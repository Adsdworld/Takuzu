<<<<<<< HEAD
<<<<<<< HEAD
#ifndef MATRICE_H

#define MATRICE_H
/****************************************
 * D�claration des #include
 ****************************************/
#include <stdint.h>


/****************************************
 * D�claration des #define
 ****************************************/
#define MATRIX_SUCCESS 0
#define MATRIX_FAILURE -1

/* Taille de la matrice 8x8 */
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
 * D�claration des variables
 ****************************************/
uint32_t pixels[MATRIX_SIZE];


/****************************************
 * D�claration des fonctions
 ****************************************/
int InitMatrix(void);
int MovePixel(void);
int8_t GetPixelX(void);
int8_t GetPixelY(void);
int SetPixelX(int8_t y);
int SetPixelY(int8_t y);
int InitMatrix();

#endif // MATRICE_H
=======
=======
>>>>>>> origin/master
#ifndef TAKUZU_H

#define TAKUZU_H

/****************************************
 * D�claration des #define
 ****************************************/
#define TAKUZU_SUCCESS 0
#define TAKUZU_FAILURE -1

#define SIZE 8
#define EMPTY 2


/****************************************
 * D�claration des variables
 ****************************************/


/****************************************
 * D�claration des fonctions
 ****************************************/
int takuzuGenerated[SIZE][SIZE];
int takuzuToSolve[SIZE][SIZE];
int takuzuToPlay[SIZE][SIZE];
void affichertakuzu(int takuzu[SIZE][SIZE]);
void TakuzuToMatrix(uint32_t* pixels, int takuzu[SIZE][SIZE]);
int TogglePixel(int x, int y);
int CompareGrids(int grid1[SIZE][SIZE], int grid2[SIZE][SIZE]);
void mainTakuzu();


#endif // TAKUZU_H
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> origin/master
