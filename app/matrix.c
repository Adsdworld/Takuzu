/**
 * @file matrix.c
 * @author Arthur de Sallier Dupin
 * @brief Matrix module, represent the matrix and functions to interact with it.
 * @version 1.1
 * @date 2025-05-02
 */
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
 * @return MATRIX_SUCCESS on success or MATRIX_FAILURE on failure.
 */
uint8_t MovePixel() {
	uint8_t error = MATRIX_SUCCESS;
	if (GetPixelX() < 0 || GetPixelX() > 7 || GetPixelY() < 0 || GetPixelY() > 7) {
		error++;
	}
	if (error != MATRIX_SUCCESS) {
		printf("[MATRIX][MovePixel][warning] Could not move to (%u, %u).\n\r", GetPixelX(), GetPixelY());
		return MATRIX_FAILURE;
	}

	TakuzuToMatrix(GetMatrixPixels(), takuzuToPlay);

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
 * @return MATRIX_SUCCESS on success or MATRIX_FAILURE on failure.
 */
uint8_t InitMatrix (){
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
 * @return MATRIX_SUCCESS on success or MATRIX_FAILURE on failure.
 */
uint8_t SetPixelX(int8_t x){
	uint8_t error = MATRIX_SUCCESS;
	if (x < 0 || x > 7) {
		error++;
	}
	if (error != MATRIX_SUCCESS) {
		printf("[MATRIX][SetPixelX][error] Could not set X to (%u).\n\r", x);
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
 * @return MATRIX_SUCCESS on success or MATRIX_FAILURE on failure.
 */
uint8_t SetPixelY(int8_t y){
	uint8_t error = MATRIX_SUCCESS;
	if (y < 0 || y > 7) {
		error++;
	}
	if (error != MATRIX_SUCCESS) {
		printf("[MATRIX][SetPixelY][error] Could not set Y to (%u).\n\r", y);
		return MATRIX_FAILURE;
	}
	matrix_pixel_y = y;
	return MATRIX_SUCCESS;
}

/**
 * @brief Gets Matrix pixels tab.
 *
 * @return tab uint32_t.
 */
uint32_t* GetMatrixPixels(void) {
	return pixels;
}

/**
 * @brief Sets matrix pixels tab.
 *
 * @return void.
 */
uint8_t SetMatrixPixels(uint8_t index, uint32_t color) {
	uint8_t error = MATRIX_SUCCESS;
	if (index < 0 || index > MATRIX_SIZE) {
		error++;
	}
	if (error != MATRIX_SUCCESS) {
		printf("[MATRIX][SetMatrixPixels][error] Could not set matrix pixel (%u) to (%lu).\n\r", index, color);
		return MATRIX_FAILURE;
	}
	pixels[index] = color;
	return MATRIX_SUCCESS;
}
