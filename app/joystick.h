#ifndef JOYSTICK_H

#define JOYSTICK_H

/****************************************
 * D�claration des #define
 ****************************************/
#define JOYSTICK_SUCCESS 0
#define JOYSTICK_FAILURE -1

#define JOYSTICK_X_PIN      GPIO_PIN_0  // PA0
#define JOYSTICK_Y_PIN      GPIO_PIN_1  // PA1
#define JOYSTICK_X_Y_PORT       GPIOA   // Port data X Y
#define JOYSTICK_KEY_PIN    GPIO_PIN_3  // PB3
#define JOYSTICK_KEY_PORT       GPIOB   // Port data KEY

#define JOYSTICK_MIN 0
#define JOYSTICK_MAX 4095
#define JOYSTICK_TOLERANCE 600  // Tol�rance autour du centre (2048)
#define JOYSTICK_CALIBRATION 100

#define JOYSTICK_BUTTON_DEBOUNCE_DELAY_MS 50
#define JOYSTICK_BUTTON_LONG_PRESS_DELAY_MS 300


/****************************************
 * D�claration des structures de donn�es
 ****************************************/
typedef void (*GenericCallback)(void);


/****************************************
 * D�claration des variables
 ****************************************/
uint16_t joystick_x_calib, joystick_y_calib;
uint16_t joystick_x, joystick_y;
GPIO_PinState joystick_button;
bool joystick_allow_move;
float angle, dx, dy;
GenericCallback button_callback;
volatile uint8_t button_state;






/****************************************
 * D�claration des fonctions
 ****************************************/
int InitJoystick(void);
int Calibrate(void);
void CalculateAngle();
void UpdateJoystickX();
void UpdateJoystickY();
void UpdateJoystickButton();
void DetectButtonAndExecuteCallback();
void joystick_button_process_ms(void);


#endif // JOYSTICK_H
