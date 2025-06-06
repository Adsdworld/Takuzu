#ifndef MATRICE_H

#define MATRICE_H
/****************************************
 * Déclaration des #include
 ****************************************/
#include <stdint.h>


/****************************************
 * Déclaration des #define
 ****************************************/
#define MATRIX_SUCCESS 0
#define MATRIX_FAILURE -1

/* Matrix size 8x8 */
#define MATRIX_SIZE 64

/* Colors */
#define CURSOR_COLOR 	0x001000
#define TAKUZU_1_COLOR	0x000010
#define TAKUZU_0_COLOR	0x100000
/** Other colors can be defined as needed, for example:
#define WS2812_COLOR_BLACK			0x000000
#define WS2812_COLOR_BLUE			0x0000FF
#define WS2812_COLOR_RED			0x00FF00
#define WS2812_COLOR_GREEN			0xFF0000
#define WS2812_COLOR_WHITE			0xFFFFFF
#define WS2812_COLOR_LIGHT_BLUE		0x000010
#define WS2812_COLOR_LIGHT_RED		0x001000
#define WS2812_COLOR_LIGHT_GREEN	0x100000
#define WS2812_COLOR_LIGHT_WHITE	0x102010
*/


/****************************************
 * Déclaration des fonctions
 ****************************************/
extern uint8_t InitMatrix(void);
extern uint8_t MovePixel(void);
extern int8_t GetPixelX(void);
extern int8_t GetPixelY(void);
extern uint8_t SetPixelX(int8_t y);
extern uint8_t SetPixelY(int8_t y);
extern uint8_t InitMatrix();
extern uint32_t* GetMatrixPixels(void);
extern uint8_t SetMatrixPixels(uint8_t, uint32_t);

#endif // MATRICE_H
