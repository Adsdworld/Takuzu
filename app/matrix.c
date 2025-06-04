#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "takuzu.h"
#include <stdbool.h>
#include "WS2812/stm32g4_ws2812.h"
#include <matrix.h>

/* Matrix pixel position */
int8_t matrix_pixel_x = 4, matrix_pixel_y = 4;

/* Matrix pixels */
uint32_t pixels[MATRIX_SIZE];

/**
 * @brief Moves the active pixel on the LED matrix.
 *
 * This function checks that the pixel coordinates are within the matrix bounds (0 to 7),
 * then updates the matrix display to move the cursor to the specified position.
 * It uses the current state of a Takuzu puzzle and overlays the cursor pixel.
 *
 * @return int MATRIX_SUCCESS or MATRIX_FAILURE.
 */
int MovePixel() {
	int error = 0;
	if (GetPixelX() < 0 || GetPixelX() > 7 || GetPixelY() < 0 || GetPixelY() > 7) {
		error++;
	}
	if (error != 0) {
		printf("[MATRIX][MovePixel][warning] Could not move to (%d, %d).\n\r", GetPixelX(), GetPixelY());
		return MATRIX_FAILURE;
	}

	TakuzuToMatrix(pixels, takuzuToPlay);

	pixels[8*GetPixelY() + GetPixelX()] = CURSOR_COLOR;

    BSP_WS2812_display(pixels, MATRIX_SIZE);
	return MATRIX_SUCCESS;
}

/**
 * @brief Initializes the LED matrix display.
 *
 * This function initializes the WS2812 LED driver and displays a test pattern
 * with a full matrix set to light red. It can be used to verify that the matrix
 * hardware is properly connected and functional.
 *
 * @return int MATRIX_SUCCESS or MATRIX_FAILURE.
 */
int InitMatrix (){
	BSP_WS2812_init();
	BSP_WS2812_display_full(WS2812_COLOR_LIGHT_RED, 64);
	return MATRIX_SUCCESS;
}

/**
 * @brief Gets the current X coordinate of the active pixel.
 *
 * @return int8_t Current X position.
 */
int8_t GetPixelX(){
	return matrix_pixel_x;
}

/**
 * @brief Gets the current Y coordinate of the active pixel.
 *
 * @return int8_t Current Y position.
 */
int8_t GetPixelY(){
	return matrix_pixel_y;
}


/**
 * @brief Sets the X coordinate of the active pixel.
 *
 * This function updates the current X position of the pixel,
 * ensuring it stays within the valid range (0 to 7).
 *
 * @param x New X coordinate.
 * @return int MATRIX_SUCCESS or MATRIX_FAILURE.
 */
int SetPixelX(int8_t x){
	int error = 0;
	if (x < 0 || x > 7) {
		error++;
	}
	if (error != 0) {
		printf("[MATRIX][SetPixelX][error] Could not set X to (%d).\n\r", x);
		return MATRIX_FAILURE;
	}
	matrix_pixel_x = x;
	return MATRIX_SUCCESS;
}

/**
 * @brief Sets the Y coordinate of the active pixel.
 *
 * This function updates the current Y position of the pixel,
 * ensuring it stays within the valid range (0 to 7).
 *
 * @param y New Y coordinate.
 * @return int MATRIX_SUCCESS or MATRIX_FAILURE.
 */
int SetPixelY(int8_t y){
	int error = 0;
	if (y < 0 || y > 7) {
		error++;
	}
	if (error != 0) {
		printf("[MATRIX][SetPixelY][error] Could not set Y to (%d).\n\r", y);
		return MATRIX_FAILURE;
	}
	matrix_pixel_y = y;
	return MATRIX_SUCCESS;
}

/* Takuzu grids */
int takuzuGenerated[SIZE][SIZE];
int takuzuToSolve[SIZE][SIZE];
int takuzuToPlay[SIZE][SIZE];

/* Store the date of when a takuzu is generated
 *
 * Takuzu generation can be impossible or take a while if the solution is complex.
 * So, we set a short delay of 200 ms to try to generate a valid takuzu.
 * We use this date and the delay to determine if we must try another random generation.
 */
uint32_t startDate;

/**
 * @brief Resets the random seed for generating Takuzu puzzles.
 *
 * This function sets the random seed to the current system tick using `HAL_GetTick()`,
 * ensuring randomness for Takuzu puzzle generation.
 */
void resetSeed() {
	startDate = HAL_GetTick();
    srand(startDate);  // set the random seed to the current 'HAL_GetTick()'
    printf("[TAKUZU][resetSeed][info] New random seed : %lu\n\r", (unsigned long)startDate);
}

/**
 * @brief Checks if the allowed time for Takuzu generation has been exceeded.
 *
 * @return true if 200ms has passed since the seed was reset, otherwise false.
 */
bool isTimeExceeded() {
    uint32_t currentTime = HAL_GetTick();
    return (currentTime - startDate) >= 200;
}

/**
 * @brief Checks if there are no repeated 3 consecutive elements in the column up to the given row.
 *
 * This ensures no invalid sequences occur vertically in the Takuzu grid.
 *
 * @param col The column index.
 * @param ligneMax The row index up to which the check is performed.
 *
 * @return true if no repeated sequences exist, false otherwise.
 */
bool max2OnColJusquaLigne(int col, int ligneMax) {
    for (int i = 0; i < ligneMax - 1; i++) {
        if (takuzuGenerated[i][col] != EMPTY &&
            takuzuGenerated[i][col] == takuzuGenerated[i+1][col] &&
            takuzuGenerated[i+1][col] == takuzuGenerated[i+2][col]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks that the number of 0's and 1's in the column is not greater than half of the SIZE.
 *
 * @param col The column index.
 * @param ligneMax The row index up to which the check is performed.
 *
 * @return true if the count of 0's and 1's is valid, false otherwise.
 */
bool compteEtVerifieColJusquaLigne(int col, int ligneMax) {
    int count0 = 0, count1 = 0;
    for (int i = 0; i <= ligneMax; i++) {
        if (takuzuGenerated[i][col] == 0) count0++;
        else if (takuzuGenerated[i][col] == 1) count1++;
    }
    return count0 <= SIZE / 2 && count1 <= SIZE / 2;
}

/**
 * @brief Checks if there are no repeated 3 consecutive elements in the row.
 *
 * @param ligne The row to check.
 *
 * @return true if no repeated sequences exist, false otherwise.
 */
bool max2OnLine(int ligne[SIZE]) {
    for (int i = 0; i < SIZE - 2; i++) {
        if (ligne[i] != EMPTY && ligne[i] == ligne[i + 1] && ligne[i + 1] == ligne[i + 2]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Checks that the number of 0's and 1's in the row is not greater than half of the size.
 *
 * @param ligne The row to check.
 *
 * @return true if the count of 0's and 1's is valid, false otherwise.
 */
bool compteEtVerifie(int ligne[SIZE]) {
    int count0 = 0, count1 = 0;
    for (int i = 0; i < SIZE; i++) {
        if (ligne[i] == 0) count0++;
        else if (ligne[i] == 1) count1++;
    }
    return count0 <= SIZE / 2 && count1 <= SIZE / 2;
}

/**
 * @brief Generates a valid line of the Takuzu puzzle.
 *
 * This recursive function fills a row of the Takuzu puzzle with 0's and 1's,
 * ensuring the rules for valid sequences are met.
 *
 * @param row The row index to fill.
 * @param col The column index to start the filling.
 *
 * @return true if a valid row is generated, false otherwise.
 */
bool generateLine(int row, int col) {

    if (col == SIZE) {
        if (!max2OnLine(takuzuGenerated[row]) || !compteEtVerifie(takuzuGenerated[row]))
            return false;
        return true;
    }

    int valeurs[2] = {0, 1};
    if (rand() % 2 == 0) {
        int tmp = valeurs[0];
        valeurs[0] = valeurs[1];
        valeurs[1] = tmp;
    }

    for (int i = 0; i < 2; i++) {
        int value = valeurs[i];
        takuzuGenerated[row][col] = value;

        if (
            max2OnLine(takuzuGenerated[row]) &&
            compteEtVerifie(takuzuGenerated[row]) &&
            max2OnColJusquaLigne(col, row) &&
            compteEtVerifieColJusquaLigne(col, row)
        ) {
            if (generateLine(row, col + 1)) return true;
        }

    }

    takuzuGenerated[row][col] = EMPTY; // Backtrack if no valid solution
    return false;
}



/**
 * @brief Generates the Takuzu puzzle.
 *
 * This function initializes the generation of a valid Takuzu puzzle by repeatedly calling
 * the recursive `generateLine` function and backtracking when necessary.
 */
void Generate() {
    printf("[TAKUZU][generate][info][init] Takuzu generation.\n\r");
	resetSeed();

    printf("[TAKUZU][generate][info][processing] Processing Takuzu generation.\n\r");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            takuzuGenerated[i][j] = EMPTY;
        }

        bool success = generateLine(i, 0);
        if (!success) {
            i -= 2; // backtrack to previous line
            if (i < -1) i = -1; // avoid infinit loop

            if (isTimeExceeded()) {
				resetSeed();
				return Generate();
			}
        }
    }

    printf("[TAKUZU][generate][info][complete] Takuzu generation completed.\n\r");
}




/**
 * @brief Displays the current Takuzu grid.
 *
 * This function prints the Takuzu grid to the console.
 *
 * @param takuzu The Takuzu grid to display.
 */
void showTakuzu(int takuzu[SIZE][SIZE]) {
    printf("[TAKUZU][showTakuzu][info][init] Show takuzu.\n");
    printf("[TAKUZU][showTakuzu][info][processing] Processing show takuzu.\n\r");

    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            if (takuzu[i][j] == EMPTY)
                printf("- ");  // Affiche "-" pour les cases vides '2'
            else
                printf("%d ", takuzu[i][j]);  // Affiche 0 ou 1
        }
        printf("\n\r");
    }
    printf("[TAKUZU][showTakuzu][info][complete] Show takuzu completed.\n\r");
}

/**
 * @brief Detects and removes patterns from a Takuzu line.
 *
 * This function looks for specific patterns (e.g., 1001, 0110) in the rows of the puzzle,
 * and removes them by setting the matching cells to EMPTY.
 *
 * @param i The row index.
 * @param ligne The line to check for patterns.
 * @param motif The pattern to detect.
 * @param motif_size The size of the pattern.
 */
void DetectLignePattern(int i, int ligne[], int motif[], int motif_size) {
    for (int j = 0; j <= SIZE - motif_size; j++) {
        int match = 1;

        for (int k = 0; k < motif_size; k++) {
            if (ligne[j + k] != motif[k]) {
                match = 0;
                break;
            }
        }

        if (match) {
            for (int k = 0; k < motif_size; k++) {
            	if (motif[0] == 1){ // on retire les 1
            		if (ligne[j + k] == 1) { // motif[k] == 1 &&
						ligne[j + k] = EMPTY;
					}
            	} else { // on retire les 0
            		if (ligne[j + k] == 0) { // motif[k] == 1 &&
						ligne[j + k] = EMPTY;
					}
            	}

            }
            return;
        }
    }
}

/**
 * @brief Removes specific patterns from the Takuzu grid.
 *
 * This function checks for specific patterns (1001, 0110, 101, 010) in each row of the Takuzu grid
 * and removes them by setting the corresponding cells to EMPTY. The function iterates over all rows
 * and applies the `DetectLignePattern` function for each pattern.
 */
void CellRemover() {
    int pattern_1001[] = {1, 0, 0, 1};
    int pattern_0110[] = {0, 1, 1, 0};
    int pattern_101[]  = {1, 0, 1};
    int pattern_010[]  = {0, 1, 0};

    for (int i = 0; i < SIZE; i++) {
        DetectLignePattern(i, takuzuToSolve[i], pattern_1001, 4);
        DetectLignePattern(i, takuzuToSolve[i], pattern_0110, 4);
        DetectLignePattern(i, takuzuToSolve[i], pattern_101, 3);
        DetectLignePattern(i, takuzuToSolve[i], pattern_010, 3);
    }
}

/**
 * @brief Converts a Takuzu grid to a pixel array for display.
 *
 * This function takes a Takuzu grid and converts it into a pixel array suitable for display on
 * an LED matrix (using WS2812). The function maps each value in the Takuzu grid (0, 1, or EMPTY)
 * to a specific color (light blue for 0, light green for 1, and black for EMPTY).
 *
 * @param pixels A pointer to the pixel array to store the color values.
 * @param takuzu A 2D array representing the Takuzu grid to be converted.
 */
void TakuzuToMatrix(uint32_t* pixels, int takuzu[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            //int index = i * SIZE + j;
        	int index = j * SIZE + i;

            switch (takuzu[i][j]) {
                case 0:
                    pixels[index] = WS2812_COLOR_LIGHT_BLUE;
                    break;
                case 1:
                    pixels[index] = WS2812_COLOR_LIGHT_GREEN;
                    break;
                case EMPTY:
                default:
                    pixels[index] = WS2812_COLOR_BLACK;
                    break;
            }
        }
    }
}

/**
 * @brief Toggles the value of a specific cell in the Takuzu grid.
 *
 * This function toggles the value of a cell at position (x, y) in the `takuzuToPlay` grid. The cell
 * goes through three possible states: 0 -> 1 -> 2 -> 0. If the cell is fixed (i.e., its value is
 * not EMPTY in the `takuzuToSolve` grid), the function prevents modification. After changing the value,
 * the grid is updated and displayed.
 *
 * @param x The row index of the cell to toggle.
 * @param y The column index of the cell to toggle.
 *
 * @return TAKUZU_SUCCESS if the operation was successful, TAKUZU_FAILURE if there was an error (e.g.,
 *         attempting to modify a fixed cell).
 */
int TogglePixel(int x, int y) {
	int error = 0;

	if (takuzuToSolve[x][y] != EMPTY) {
	    printf("[TAKUZU][TogglePixel][info][player] Impossible fo modify a fix cell(%d, %d).\n\r", x, y);
	    return TAKUZU_FAILURE;
	}

	if (takuzuToPlay[x][y] == 0) {
		takuzuToPlay[x][y] = 1;
	} else if(takuzuToPlay[x][y] == 1) {
		takuzuToPlay[x][y] = 2;
	} else {
		takuzuToPlay[x][y] = 0;
	}
	error += MovePixel();
	showTakuzu(takuzuGenerated);
	showTakuzu(takuzuToPlay);

	if (error == 0) {
	    return TAKUZU_SUCCESS;
	}

	return TAKUZU_FAILURE;
}

/**
 * @brief Compares two Takuzu grids to check if they are identical.
 *
 * This function compares two Takuzu grids (`grid1` and `grid2`) to see if they are identical. It
 * compares each corresponding cell in both grids. If any difference is found, the function returns false.
 *
 * @param grid1 The first grid to compare.
 * @param grid2 The second grid to compare.
 *
 * @return true if the grids are identical, false otherwise.
 */
int CompareGrids(int grid1[SIZE][SIZE], int grid2[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid1[i][j] != grid2[i][j]) {
                return 0; // found a difference
            }
        }
    }
    return 1; // grids are matching
}

/**
 * @brief Main function to generate, display, and modify a Takuzu puzzle.
 *
 * This function generates a Takuzu puzzle, displays it, removes specific patterns, and prepares
 * the puzzle for gameplay. It creates a copy of the generated Takuzu puzzle, removes patterns from
 * it, and sets up the initial grid for the player to modify.
 */
void mainTakuzu() {
	Generate();
	showTakuzu(takuzuGenerated);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			takuzuToSolve[i][j] = takuzuGenerated[i][j];
		}
	}
	CellRemover();
	showTakuzu(takuzuToSolve);
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			takuzuToPlay[i][j] = takuzuToSolve[i][j];
		}
	}
}


