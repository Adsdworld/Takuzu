/**
 *******************************************************************************
 * @file 	main.c
 * @author  de Sallier Dupin Arthur
 * @date 	14 04, 2025
 * @brief	Fichier principal de votre projet sur carte Nucléo STM32G431KB
 *******************************************************************************
 */

#include "config.h"
#include "stm32g4_sys.h"
#include "stm32g4_systick.h"
#include "stm32g4_gpio.h"
#include "stm32g4_uart.h"
#include "stm32g4_utils.h"
#include <stdio.h>

/* our game include */
#include "game.h"

/* Joystick */
#include "joystick.h"

/* Matrix */
#include "matrix.h"

#define MAIN_SUCCESS 0
#define MAIN_FAILURE -1

/*bool char_received(uart_id_t uart_id) // not needed
{
	{
		BSP_UART_get_next_byte(uart_id);
		return true;
	}
	else
		return false;
}*/

/*void heartbeat(void) // not needed
{
	while(! char_received(UART2_ID) )
	{
		write_LED(true);
		HAL_Delay(50);
		write_LED(false);
		HAL_Delay(1500);
	}
}*/

/**
  * @brief  Point d'entrée de votre application
  */
int main(void)
{
	/* This line must remain the first in your main!
	 * It initializes all the low-level layers of the drivers (Hardware Abstraction Layer),
	 * which is a necessary prerequisite for the execution of the following lines.
	 */
	HAL_Init();

	/* Initialization of the peripherals used in your program */
	BSP_GPIO_enable();
	BSP_UART_init(UART2_ID,115200);

	/* Indicates that printf outputs are redirected to UART2 */
	BSP_SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\r"
	          "          JJJJJJJJJJJ                                                              tttt            iiii                      kkkkkkkk\n\r"
	          "          J:::::::::J                                                           ttt:::t           i::::i                     k::::::k\n\r"
	          "          J:::::::::J                                                           t:::::t            iiii                      k::::::k\n\r"
	          "          JJ:::::::JJ                                                           t:::::t                                      k::::::k\n\r"
	          "            J:::::J   ooooooooooo yyyyyyy           yyyyyyy  ssssssssss   ttttttt:::::ttttttt    iiiiiii     cccccccccccccccc k:::::k    kkkkkkk\n\r"
	          "            J:::::J oo:::::::::::ooy:::::y         y:::::y ss::::::::::s  t:::::::::::::::::t    i:::::i   cc:::::::::::::::c k:::::k   k:::::k\n\r"
	          "            J:::::Jo:::::::::::::::oy:::::y       y:::::yss:::::::::::::s t:::::::::::::::::t     i::::i  c:::::::::::::::::c k:::::k  k:::::k\n\r"
	          "            J:::::jo:::::ooooo:::::o y:::::y     y:::::y s::::::ssss:::::stttttt:::::::tttttt     i::::i c:::::::cccccc:::::c k:::::k k:::::k\n\r"
	          "            J:::::Jo::::o     o::::o  y:::::y   y:::::y   s:::::s  ssssss       t:::::t           i::::i c::::::c     ccccccc k::::::k:::::k\n\r"
	          "JJJJJJJ     J:::::Jo::::o     o::::o   y:::::y y:::::y      s::::::s            t:::::t           i::::i c:::::c              k:::::::::::k\n\r"
	          "J:::::J     J:::::Jo::::o     o::::o    y:::::y:::::y          s::::::s         t:::::t           i::::i c:::::c              k:::::::::::k\n\r"
	          "J::::::J   J::::::Jo::::o     o::::o     y:::::::::y     ssssss   s:::::s       t:::::t    tttttt i::::i c::::::c     ccccccc k::::::k:::::k\n\r"
	          "J:::::::JJJ:::::::Jo:::::ooooo:::::o      y:::::::y      s:::::ssss::::::s      t::::::tttt:::::ti::::::ic:::::::cccccc:::::ck::::::k k:::::k\n\r"
	          " JJ:::::::::::::JJ o:::::::::::::::o       y:::::y       s::::::::::::::s       tt::::::::::::::ti::::::i c:::::::::::::::::ck::::::k  k:::::k\n\r"
	          "   JJ:::::::::JJ    oo:::::::::::oo       y:::::y         s:::::::::::ss          tt:::::::::::tti::::::i  cc:::::::::::::::ck::::::k   k:::::k\n\r"
	          "     JJJJJJJJJ        ooooooooooo        y:::::y           sssssssssss              ttttttttttt  iiiiiiii    cccccccccccccccckkkkkkkk    kkkkkkk\n\r"
	          "                                        y:::::y\n\r"
	          "                                       y:::::y\n\r"
	          "                                      y:::::y\n\r"
	          "                                     y:::::y\n\r"
	          "                                    yyyyyyy\n\r\n\r");


	int errorMatrice = InitMatrix();
	int errorJoystick = InitJoystick();

    if (errorMatrice != MATRIX_SUCCESS) {
        printf("[MAIN][main][error] Failed to initialize the matrix.\n\r");
        return MAIN_FAILURE;
    }

    if (errorJoystick != JOYSTICK_SUCCESS) {
        printf("[MAIN][main][error] Failed to initialize the joystick.\n\r");
        return MAIN_FAILURE;
    }

    printf("[MAIN][main][info] Successfully initialized components!\r\n\r\n");

    /* Background task, infinite loop... whatever you call it, you're never getting out of it */
	while (1)
	{
		int errorStartGame = StartGame();
		if (errorStartGame != 0) {
			printf("[MAIN][main][error] Failed to start the game.\r\n");
			return -1;
		}
	}
}
