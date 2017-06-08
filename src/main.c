// from https://gist.github.com/kripken/59c67556dc03bb6d57052fedef1e61ab
// compile with: emcc main.c -Os -s WASM=1 -s SIDE_MODULE=1 -o main.wasm
// run with: emrun --port 8080 .
#include <stdlib.h>
#include <stdint.h>

/* 8x8 Bayer ordered dithering. Inspired by Lee Daniel Crocker's http://www.efg2.com/Lab/Library/ImageProcessing/DHALF.TXT */
void grayscale_dither_ordered(int width, int height, uint8_t *data, uint8_t *processed_data)
{	
	uint8_t pixel;
	const uint8_t pattern[8][8] = {
	    { 0, 32,  8, 40,  2, 34, 10, 42},   /* 8x8 Bayer ordered dithering  */
	    {48, 16, 56, 24, 50, 18, 58, 26},   /* pattern.  Each input pixel   */
	    {12, 44,  4, 36, 14, 46,  6, 38},   /* is scaled to the 0..63 range */
	    {60, 28, 52, 20, 62, 30, 54, 22},   /* before looking in this table */
	    { 3, 35, 11, 43,  1, 33,  9, 41},   /* to determine the action.     */
	    {51, 19, 59, 27, 49, 17, 57, 25},
	    {15, 47,  7, 39, 13, 45,  5, 37},
	    {63, 31, 55, 23, 61, 29, 53, 21} };

	for (int i = 0; i < height; i++) {
	    for (int j = 0; j < width; j++) {
	        pixel = data[width*i + j] >> 2; // scaled to 0..63 for Bayer matrix comparison

	        if (pixel > pattern[j & 7][i & 7])
	            processed_data[width*i + j] = 255;
	        else
	            processed_data[width*i + j] = 0;
	    }
	}
}