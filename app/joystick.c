#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "takuzu.h"
#include <stdbool.h>
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include "stm32g4_adc.h"
#include <math.h>

/* For colors */
#include "WS2812/stm32g4_ws2812.h"

/* Joystick */
#include "joystick.h"

/* Joystick calibrated position */
uint16_t joystick_x_calib, joystick_y_calib;

/* Joystick position */
uint16_t joystick_x, joystick_y;

/* Joystick button */
GPIO_PinState joystick_button;

/* Allow joystick move */
bool joystick_allow_move = false;

/* Angle and distance */
float angle, dx, dy;

/* A function that return void could be set, if not void will raise a warning because output is not handle */
GenericCallback button_callback = NULL;

/* BUTTON_RELEASE, BUTTON_PRESS */
volatile uint8_t button_state = 0;

/* Counter */
volatile uint32_t debounce_timer = 0;

/* Press duration */
volatile uint32_t button_press_duration = 0;

/* JOYSTICK_BUTTON_LONG_PRESS_FLAG_DOWN, JOYSTICK_BUTTON_LONG_PRESS_FLAG_UP : execute button_callback() */
volatile uint8_t button_event_pending = 0;

/**
 * @brief Initializes the joystick hardware.
 *
 * This function configures the GPIO pins used by the joystick:
 * - The joystick button (digital input with pull-up)
 * - The X and Y axes (analog inputs without pull-up/pull-down)
 *
 * It also initializes the ADC module required for reading analog joystick values,
 * and performs a calibration routine.
 *
 * @return JOYSTICK_SUCCESS on success or JOYSTICK_FAILURE on failure.
 */
uint8_t InitJoystick (){
	uint8_t error = 0;
	/* Joystick pins initialisation */
	BSP_GPIO_pin_config(JOYSTICK_KEY_PORT, JOYSTICK_KEY_PIN, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_ADC_init();
	BSP_GPIO_pin_config(JOYSTICK_X_Y_PORT, JOYSTICK_X_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(JOYSTICK_X_Y_PORT, JOYSTICK_Y_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);

	error += Calibrate();
	if (error != JOYSTICK_SUCCESS) {
	    printf("[JOYSTICK][InitJoystick][error] %d errors occured during Calibrate.\n\r", error);
		return JOYSTICK_FAILURE;
	}
	return JOYSTICK_SUCCESS;
}

/**
 * @brief Processes joystick button events every millisecond.
 *
 * This function is intended to be called periodically (e.g., every millisecond)
 * to handle button debouncing and long press detection.
 * @return void
 */
void joystick_button_process_ms(void) {
    if (debounce_timer > 0) debounce_timer--;
    if (button_press_duration > 0) button_press_duration++;
}

/**
 * @brief Detects joystick button presses and executes the associated callback.
 *
 * This function checks the state of the joystick button, manages debouncing,
 * and triggers a callback function when a button press is detected.
 * It distinguishes between short and long presses based on predefined delays.
 * @return void
 */
void DetectButtonAndExecuteCallback() {
	UpdateJoystickButton();

    /* If button is pressed and debounce has ended */
    if (joystick_button == GPIO_PIN_RESET && debounce_timer == 0 && button_state == 0) {
        //printf("[DEBUG] Bouton press (start)\r\n");
        button_state = BUTTON_PRESS;
        debounce_timer = JOYSTICK_BUTTON_DEBOUNCE_DELAY_MS;
        button_press_duration = 1;

    }

    /* If the button is released and it was pressed */
    if (joystick_button == GPIO_PIN_SET && button_state == 1) {
        //printf("[DEBUG] Bouton release (end)\r\n");

        button_state = BUTTON_RELEASE;
        debounce_timer = JOYSTICK_BUTTON_DEBOUNCE_DELAY_MS;

        /**
         * If the button was pressed for a long time, we consider it a long press
         * and trigger the callback function.
         */
        if (button_press_duration >= JOYSTICK_BUTTON_LONG_PRESS_DELAY_MS) {
            //printf("[DEBUG] Long press, flag up\r\n");

            button_event_pending = JOYSTICK_BUTTON_LONG_PRESS_FLAG_UP;
        }

        button_press_duration = 0;
    }

    /* If a button event is pending, execute the callback function.
     * This allows the button press to be processed without blocking the main loop.
     */
    if (button_event_pending == JOYSTICK_BUTTON_LONG_PRESS_FLAG_UP) {
        //printf("[DEBUG] TogglePixel event !\r\n");
        button_callback();
        button_event_pending = JOYSTICK_BUTTON_LONG_PRESS_FLAG_DOWN;
    }
}

/**
 * @brief Calibrates the joystick's neutral position.
 *
 * This function performs a calibration of the joystick by sampling its X and Y values multiple times,
 * averaging them to determine the neutral (centered) position. This is useful to offset hardware drift
 * or joystick imperfections.
 *
 * Visual feedback is given through a WS2812 LED matrix, which turns red during calibration
 * and off afterward. Calibration status is logged at each step using printf.
 *
 * The ADC readings are gathered using the `UpdateJoystickX()` and `UpdateJoystickY()` functions.
 *
 * @return JOYSTICK_SUCCESS on success or JOYSTICK_FAILURE on failure.
 */
uint8_t Calibrate() {
    printf("[JOYSTICK][Calibrate][info][init] Joystick calibration.\n\r");
    uint32_t sum_x = 0, sum_y = 0;
    BSP_WS2812_display_full(WS2812_COLOR_LIGHT_RED, 64);


    printf("[JOYSTICK][Calibrate][info][processing] Processing joystick calibration.\n\r");
    for (uint8_t i = 0; i < JOYSTICK_CALIBRATION; i++) {
        HAL_Delay(10);
        UpdateJoystickX();
        UpdateJoystickY();
        sum_x += joystick_x;
        sum_y += joystick_y;
    }

    joystick_x_calib = sum_x / JOYSTICK_CALIBRATION;
    joystick_y_calib = sum_y / JOYSTICK_CALIBRATION;

    printf("[JOYSTICK][Calibrate][info][complete] Joyctick calibration completed.\n\r");
    printf("X calibre: %d\n\r", joystick_x_calib);
    printf("Y calibre: %d\n\r", joystick_y_calib);
    BSP_WS2812_display_full(WS2812_COLOR_BLACK, 64);

    return JOYSTICK_SUCCESS;
}

/**
 * @brief Displays the current raw state of the joystick.
 *
 * This function prints the current digital state of the joystick button and
 * the analog values of the X and Y axes to the UART console.
 *
 * It is useful for debugging and verifying that the joystick hardware and ADC are working correctly.
 * @return void
 */
void JoystickDisplay () {
    printf("KEY STATE: %d\n\r", HAL_GPIO_ReadPin(JOYSTICK_KEY_PORT, JOYSTICK_KEY_PIN));
    printf("X STATE: %04d Y STATE: %04d\n\r", BSP_ADC_getValue(ADC_1), BSP_ADC_getValue(ADC_2));
}

/**
 * @brief Calculates the angle of the joystick from the calibrated center position.
 *
 * This function computes the angle between the joystick's current position and the calibrated center
 * using the `atan2` function. The resulting angle is expressed in degrees.
 * The calculation is based on the difference between the current joystick X and Y positions
 * and their respective calibration values.
 *
 * @note The angle is calculated using the formula:
 *       angle = atan2(dy, dx) * (180.0 / M_PI)
 * @return void
 */
void CalculateAngle() {
    dx = joystick_x - joystick_x_calib;
    dy = joystick_y - joystick_y_calib;
    angle = atan2(dy, dx) * (180.0 / M_PI);
}

/**
 * @brief Gets the current angle of the joystick.
 *
 * @return void.
 */
float GetAngle() {
	return angle;
}


/**
 * @brief Updates the X axis value of the joystick.
 *
 * This function retrieves the current ADC value for the joystick's X axis using `BSP_ADC_getValue()`
 * and updates the `joystick_x` variable.
 * @return void
 */
void UpdateJoystickX() {
    joystick_x = BSP_ADC_getValue(ADC_1);
}

/**
 * @brief Updates the Y axis value of the joystick.
 *
 * This function retrieves the current ADC value for the joystick's Y axis using `BSP_ADC_getValue()`
 * and updates the `joystick_y` variable.
 * return void
 */
void UpdateJoystickY() {
    joystick_y = BSP_ADC_getValue(ADC_2);
}

/**
 * @brief Updates the joystick button state.
 *
 * This function reads the current state of the joystick button (pressed or not) using `HAL_GPIO_ReadPin()`
 * and updates the `joystick_button` variable.
 *
 * @note `GPIO_PIN_RESET` (LOW), `GPIO_PIN_SET` (HIGH).
 * @return void
 */
void UpdateJoystickButton() {
	joystick_button = HAL_GPIO_ReadPin(JOYSTICK_KEY_PORT, JOYSTICK_KEY_PIN);
}

/**
 * @brief Sets the calibrated X value of the joystick.
 *
 * @param value The new calibrated X value.
 */
void SetJoystickXCalib(uint16_t value) {
    joystick_x_calib = value;
}

/**
 * @brief Sets the calibrated Y value of the joystick.
 *
 * @param value The new calibrated Y value.
 */
void SetJoystickYCalib(uint16_t value) {
    joystick_y_calib = value;
}

/**
 * @brief Sets the current X position of the joystick.
 *
 * @param value The new X position.
 */
void SetJoystickX(uint16_t value) {
    joystick_x = value;
}

/**
 * @brief Sets the current Y position of the joystick.
 *
 * @param value The new Y position.
 */
void SetJoystickY(uint16_t value) {
    joystick_y = value;
}

/**
 * @brief Gets the calibrated X value of the joystick.
 *
 * @return uint16_t The calibrated X value.
 */
uint16_t GetJoystickXCalib(void) {
    return joystick_x_calib;
}

/**
 * @brief Gets the calibrated Y value of the joystick.
 *
 * @return uint16_t The calibrated Y value.
 */
uint16_t GetJoystickYCalib(void) {
    return joystick_y_calib;
}

/**
 * @brief Gets the current X position of the joystick.
 *
 * @return uint16_t The current X position.
 */
uint16_t GetJoystickX(void) {
    return joystick_x;
}

/**
 * @brief Gets the current Y position of the joystick.
 *
 * @return uint16_t The current Y position.
 */
uint16_t GetJoystickY(void) {
    return joystick_y;
}

/**
 * @brief Gets if a move is allowed.
 *
 * @return void.
 */
bool GetJoystickAllowMove(){
	return joystick_allow_move;
}

/**
 * @brief Sets if a move is allowed.
 *
 * @param bool allow move.
 */
void SetJoystickAllowMove(bool allow_move){
	joystick_allow_move = allow_move;
}

