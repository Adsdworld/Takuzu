#ifndef JOYSTICK_H

#define JOYSTICK_H

/****************************************
 * Déclaration des #define
 ****************************************/
#define JOYSTICK_SUCCESS 0
#define JOYSTICK_FAILURE -1

#define JOYSTICK_X_PIN      GPIO_PIN_0  // P0
#define JOYSTICK_Y_PIN      GPIO_PIN_1  // P1
#define JOYSTICK_X_Y_PORT       GPIOA   // Port data X Y
#define JOYSTICK_KEY_PIN    GPIO_PIN_3  // P3
#define JOYSTICK_KEY_PORT       GPIOB   // Port data KEY

#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 4095
#define JOYSTICK_TOLERANCE 600 // ADC 12 bits
#define JOYSTICK_CALIBRATION 100

#define JOYSTICK_BUTTON_DEBOUNCE_DELAY_MS 50
#define JOYSTICK_BUTTON_LONG_PRESS_DELAY_MS 300

#define BUTTON_PRESS 1
#define BUTTON_RELEASE 0

#define JOYSTICK_BUTTON_LONG_PRESS_FLAG_UP 1
#define JOYSTICK_BUTTON_LONG_PRESS_FLAG_DOWN 0


/****************************************
 * Déclaration des structures de données
 ****************************************/
typedef void (*GenericCallback)(void);


/****************************************
 * Déclaration des variables
 ****************************************/
//extern GPIO_PinState joystick_button;
extern bool joystick_allow_move;
extern float angle, dx, dy;
extern GenericCallback button_callback;
extern volatile uint8_t button_state;


/****************************************
 * Déclaration des fonctions
 ****************************************/
extern uint8_t InitJoystick(void);
extern uint8_t Calibrate(void);
extern void CalculateAngle();
extern void UpdateJoystickX();
extern void UpdateJoystickY();
extern void UpdateJoystickButton();
extern void DetectButtonAndExecuteCallback();
extern void joystick_button_process_ms(void);
extern uint16_t getJoystickX(void);
extern uint16_t getJoystickY(void);
extern uint16_t getJoystickXCalib(void);
extern uint16_t getJoystickYCalib(void);

#endif // JOYSTICK_H
