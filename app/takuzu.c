#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "takuzu.h"
#include <stdbool.h>
#include "WS2812/stm32g4_ws2812.h"

/* Takuzu grids */
uint8_t takuzuGenerated[SIZE][SIZE];
uint8_t takuzuToSolve[SIZE][SIZE];
uint8_t takuzuToPlay[SIZE][SIZE];

/* Store the start date of when a takuzu is generated
 *
 * Takuzu generation can be impossible or take a while if the solution is complex. 2^^64 possibilities
 * So, we set a short delay of 200 ms to try to generate a valid takuzu quickly.
 * We use this date and the delay to determine if we must try another random generation.
 */
uint32_t startDate;

/**
 * @brief Resets the random seed for generating Takuzu.
 *
 * This function sets the random seed to the current system tick using `HAL_GetTick()`,
 * ensuring randomness for Takuzu generation.
 * @return void
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
bool max2OnColJusquaLigne(uint8_t col, uint8_t ligneMax) {
    for (uint8_t i = 0; i < ligneMax - 1; i++) {
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
bool compteEtVerifieColJusquaLigne(uint8_t col, uint8_t ligneMax) {
	uint8_t count0 = 0, count1 = 0;
    for (uint8_t i = 0; i <= ligneMax; i++) {
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
bool max2OnLine(uint8_t ligne[SIZE]) {
    for (uint8_t i = 0; i < SIZE - 2; i++) {
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
bool compteEtVerifie(uint8_t ligne[SIZE]) {
	uint8_t count0 = 0, count1 = 0;
    for (uint8_t i = 0; i < SIZE; i++) {
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
bool generateLine(uint8_t row, uint8_t col) {

    if (col == SIZE) {
        if (!max2OnLine(takuzuGenerated[row]) || !compteEtVerifie(takuzuGenerated[row]))
            return false;
        return true;
    }

    uint8_t valeurs[2] = {0, 1};
    if (rand() % 2 == 0) {
    	uint8_t tmp = valeurs[0];
        valeurs[0] = valeurs[1];
        valeurs[1] = tmp;
    }

    for (uint8_t i = 0; i < 2; i++) {
    	uint8_t value = valeurs[i];
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
 * @return void
 */
void Generate() {
    printf("[TAKUZU][generate][info][init] Takuzu generation.\n\r");
	resetSeed();

    printf("[TAKUZU][generate][info][processing] Processing Takuzu generation.\n\r");
    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            takuzuGenerated[i][j] = EMPTY;
        }

        bool success = generateLine(i, 0);
        if (!success) {
            i -= 2; // backtrack to previous line
            if (i < -1) i = -1;

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
 * @return void
 */
void showTakuzu(uint8_t takuzu[SIZE][SIZE]) {
    printf("[TAKUZU][showTakuzu][info][init] Show takuzu.\n");
    printf("[TAKUZU][showTakuzu][info][processing] Processing show takuzu.\n\r");

    for (uint8_t j = 0; j < SIZE; j++) {
        for (uint8_t i = 0; i < SIZE; i++) {
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
 * @return void
 */
void DetectLignePattern(uint8_t i, uint8_t ligne[], uint8_t motif[], uint8_t motif_size) {
    for (uint8_t j = 0; j <= SIZE - motif_size; j++) {
    	uint8_t match = 1;

        for (uint8_t k = 0; k < motif_size; k++) {
            if (ligne[j + k] != motif[k]) {
                match = 0;
                break;
            }
        }

        if (match) {
            for (uint8_t k = 0; k < motif_size; k++) {
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
 * @return void
 */
void CellRemover() {
	uint8_t pattern_1001[] = {1, 0, 0, 1};
	uint8_t pattern_0110[] = {0, 1, 1, 0};
	uint8_t pattern_101[]  = {1, 0, 1};
	uint8_t pattern_010[]  = {0, 1, 0};

    for (uint8_t i = 0; i < SIZE; i++) {
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
 * @return void
 */
void TakuzuToMatrix(uint32_t* pixels, uint8_t takuzu[SIZE][SIZE]) {
    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
            //uint8_t index = i * SIZE + j;
        	uint8_t index = j * SIZE + i;

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
uint8_t TogglePixel(uint8_t x, uint8_t y) {
	uint8_t error = 0;

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
 * @brief Toggles the value of the current pixel in the Takuzu grid.
 *
 * This function toggles the value of the pixel at the current position (as defined by `GetPixelX()` and
 * `GetPixelY()`). It calls `TogglePixel` with the current pixel coordinates.
 *
 * @return void
 */
void ToggleCurrentPixel() {
	TogglePixel(GetPixelX(), GetPixelY());
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
 * @return 1 if the grids are identical, 0 otherwise.
 */
uint8_t CompareGrids(uint8_t grid1[SIZE][SIZE], uint8_t grid2[SIZE][SIZE]) {
    for (uint8_t i = 0; i < SIZE; i++) {
        for (uint8_t j = 0; j < SIZE; j++) {
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
 * @return void
 */
void mainTakuzu() {
	Generate();
	showTakuzu(takuzuGenerated);

	for (uint8_t i = 0; i < SIZE; i++) {
		for (uint8_t j = 0; j < SIZE; j++) {
			takuzuToSolve[i][j] = takuzuGenerated[i][j];
		}
	}
	CellRemover();
	showTakuzu(takuzuToSolve);
	for (uint8_t i = 0; i < SIZE; i++) {
		for (uint8_t j = 0; j < SIZE; j++) {
			takuzuToPlay[i][j] = takuzuToSolve[i][j];
		}
	}
}


