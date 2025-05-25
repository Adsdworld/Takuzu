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

/* Joystcik calibrate position */
uint16_t joystick_x_calib, joystick_y_calib;

/* Joystick position */
uint16_t joystick_x, joystick_y;

/* Joystick button */
GPIO_PinState joystick_button;

/* Allow joystick move */
bool joystick_allow_move = false;

/* Angle and distance */
float angle;
float dx;
float dy;

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
 * @return int JOYSTICK_SUCCESS or JOYSTICK_FAILURE.
 */
int InitJoystick (){
	int error = 0;
	/* Joystick pins initialisation */
	BSP_GPIO_pin_config(JOYSTICK_KEY_PORT, JOYSTICK_KEY_PIN, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_ADC_init();
	BSP_GPIO_pin_config(JOYSTICK_X_Y_PORT, JOYSTICK_X_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);
	BSP_GPIO_pin_config(JOYSTICK_X_Y_PORT, JOYSTICK_Y_PIN, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, GPIO_NO_AF);

	error += Calibrate();
	if (error == 0) {
		return JOYSTICK_SUCCESS;
	}
    printf("[JOYSTICK][InitJoystick][error] %d errors occured during InitJoystick.\n\r", error);
	return JOYSTICK_FAILURE;
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
 * @return int JOYSTICK_SUCCESS or JOYSTICK_FAILURE.
 */
int Calibrate() {
    printf("[JOYSTICK][Calibrate][info][init] Joystick calibration.\n\r");
    uint32_t sum_x = 0, sum_y = 0;
    BSP_WS2812_display_full(WS2812_COLOR_LIGHT_RED, 64);


    printf("[JOYSTICK][Calibrate][info][processing] Processing joystick calibration.\n\r");
    for (int i = 0; i < JOYSTICK_CALIBRATION; i++) {
        HAL_Delay(10);  // Petite pause entre les lectures
        UpdateJoystickX();
        UpdateJoystickY();
        sum_x += joystick_x;  // Read ADC value for X
        sum_y += joystick_y;  // Read ADC value for Y
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
 */
void CalculateAngle() {
    dx = joystick_x - joystick_x_calib;
    dy = joystick_y - joystick_y_calib;
    angle = atan2(dy, dx) * (180.0 / M_PI);
}

/**
 * @brief Updates the X axis value of the joystick.
 *
 * This function retrieves the current ADC value for the joystick's X axis using `BSP_ADC_getValue()`
 * and updates the `joystick_x` variable.
 */
void UpdateJoystickX() {
    joystick_x = BSP_ADC_getValue(ADC_1);
}

/**
 * @brief Updates the Y axis value of the joystick.
 *
 * This function retrieves the current ADC value for the joystick's Y axis using `BSP_ADC_getValue()`
 * and updates the `joystick_y` variable.
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
 */
void UpdateJoystickButton() {
	joystick_button = HAL_GPIO_ReadPin(JOYSTICK_KEY_PORT, JOYSTICK_KEY_PIN);
}
