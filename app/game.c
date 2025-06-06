#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "stm32g4_adc.h"
#include <stdlib.h>
#include "stm32g4_systick.h"
#include "game.h"

/* Takuzu */
#include "takuzu.h"

/* Joystick */
#include "joystick.h"

/* Matrix */
#include "matrix.h"

/**
 * @brief Initialize the game, configure callbacks, and prepare the game environment.
 * @return GAME_SUCCESS on success, GAME_FAILURE on failure.
 */
uint8_t InitGame () {
	uint8_t error = GAME_SUCCESS;
	CalculateAngle();
    error += MovePixel();

    if (error != MATRIX_SUCCESS) {
        printf("[GAME][InitGame][error] Failed to move pixel.\r\n");
        return GAME_FAILURE;
    }

	BSP_systick_add_callback_function(&DetectButtonAndExecuteCallback);
	BSP_systick_add_callback_function(&joystick_button_process_ms);
	SetButtonCallback(&ToggleCurrentPixel);
	return GAME_SUCCESS;
}

/**
 * @brief Make a move on the matrix and temporarily disable movement.
 * @return void
 */
void MakeMove() {
	SetJoystickAllowMove(false);
    MovePixel();
}

/**
 * @brief Main game loop, handles joystick input and pixel movement.
 * @return void
 */
void MainGame() {

    /* Update joystick values */
    UpdateJoystickX();
    UpdateJoystickY();

    /* Calculate angle of the joystick if allowed to move */
    if (GetJoystickAllowMove() == true) {
    	CalculateAngle();
    }

    /* If joystick button is press handle it */
    if (GetButtonState() == BUTTON_PRESS) {
    	SetJoystickAllowMove(false);
    }

    /* Else if, check if joystick is in the central zone */
    else if ((GetJoystickX() >= (GetJoystickXCalib() - JOYSTICK_TOLERANCE)) &&
             (GetJoystickX() <= (GetJoystickXCalib() + JOYSTICK_TOLERANCE)) &&
             (GetJoystickY() >= (GetJoystickYCalib() - JOYSTICK_TOLERANCE)) &&
             (GetJoystickY() <= (GetJoystickYCalib() + JOYSTICK_TOLERANCE))) {

    	SetJoystickAllowMove(true);
        HAL_Delay(50);
    }

    /* Else if, joystick is not in the central zone, move the pixel */
    else if (GetJoystickAllowMove()) {

    	if (GetAngle() >= -45 && GetAngle() <= 45) { /* Left */
    		if (GetPixelX() > 0) {
    			SetPixelX(GetPixelX()-1);
    			MakeMove();
    			//printf("[GAME][StartGame][debug] Left\r\n");
    		}
		} else if (GetAngle() > 45 && GetAngle() <= 135) { /* Bottom */
			if (GetPixelY() < 7) {
				SetPixelY(GetPixelY()+1);
				MakeMove();
				//printf("[GAME][StartGame][debug] Bottom\r\n");
			}
		} else if (GetAngle() < -45 && GetAngle() >= -135) { /* Top */
			if (GetPixelY() > 0) {
				SetPixelY(GetPixelY()-1);
				MakeMove();
				//printf("[GAME][StartGame][debug] Top\r\n");
			}
		} else {
			if (GetPixelX() < 7) { /* Right */
				SetPixelX(GetPixelX()+1);
				MakeMove();
				//printf("[GAME][StartGame][debug] Right\r\n");
			}
		}
    }
}

/**
* @brief  End the game and release associated resources.
* @return void
*/
void EndGame () {
	BSP_systick_remove_callback_function(&DetectButtonAndExecuteCallback);
	BSP_systick_remove_callback_function(&joystick_button_process_ms);
	SetButtonCallback(NULL);
}

/**
 * @brief  Start the game by initializing it and running the main game loop.
 * @return GAME_SUCCESS on success, GAME_FAILURE on failure.
 */
uint8_t StartGame() {
	uint8_t error = InitGame();
	if (error != GAME_SUCCESS) {
		printf("[GAME][StartGame][error] Failed to initialize the game.\r\n");
		return GAME_FAILURE;
	}

	/* Generate takuzu */
	mainTakuzu();

	/* Playing while takuzu is not solve */
	while(!CompareGrids(takuzuGenerated, takuzuToPlay)) {
		MainGame();
	}

	EndGame();

	printf("[GAME][StartGame][info] Win !\n\r");
	return GAME_SUCCESS;
}
