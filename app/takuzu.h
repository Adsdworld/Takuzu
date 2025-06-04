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
void ToggleCurrentPixel();
int CompareGrids(int grid1[SIZE][SIZE], int grid2[SIZE][SIZE]);
void mainTakuzu();

#endif // TAKUZU_H
