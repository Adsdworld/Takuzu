#ifndef TAKUZU_H

#define TAKUZU_H

/****************************************
 * Déclaration des #define
 ****************************************/
#define TAKUZU_SUCCESS 0
#define TAKUZU_FAILURE -1
#define SIZE 8
#define EMPTY 2


/****************************************
 * Déclaration des variables
 ****************************************/


/****************************************
 * Déclaration des fonctions
 ****************************************/
extern uint8_t takuzuGenerated[SIZE][SIZE];
extern uint8_t takuzuToSolve[SIZE][SIZE];
extern uint8_t takuzuToPlay[SIZE][SIZE];
extern void affichertakuzu(uint8_t takuzu[SIZE][SIZE]);
extern void TakuzuToMatrix(uint32_t* pixels, uint8_t takuzu[SIZE][SIZE]);
extern uint8_t TogglePixel(uint8_t x, uint8_t y);
extern void ToggleCurrentPixel();
extern uint8_t CompareGrids(uint8_t grid1[SIZE][SIZE], uint8_t grid2[SIZE][SIZE]);
extern void mainTakuzu();

#endif // TAKUZU_H
