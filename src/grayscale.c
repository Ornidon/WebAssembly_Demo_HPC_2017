#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "immintrin.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define COMPONENT_GRAYSCALE 1
#define COMPONENT_RGB 3

/* PNG format allows for padding between rows of data */
#define PNG_STRIDE_IN_BYTES 0

#define SRC_PATH "img_grayscale.png"
#define DST_PATH "dithered.png"


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



int main (int argc, char *argv[]){
	// Init
	FILE *fimg;
	int n;
	int width;
  	int height;
	uint8_t *data;
	uint8_t *processed_data;

	// Load image
	fimg = fopen(SRC_PATH, "rb");
    if (!fimg) {
        fprintf(stderr, "[%s] fopen error (%s)\n", __func__, SRC_PATH);
        perror(__func__);
        exit(EXIT_FAILURE);
    }
	
	data = stbi_load(SRC_PATH, &width, &height, &n, 0);
    if (!data) {
        fprintf(stderr, "[%s] stbi_load() returned NULL\n", __func__);
        exit(EXIT_FAILURE);
    }

	processed_data= malloc(width * height);
    if (!processed_data) {
        fprintf(stderr, "[%s] grayscale malloc error\n", __func__);
        perror(__func__);
        exit(EXIT_FAILURE);
    }

	fprintf(stderr, "[%s] image %s loaded (%d components, %dx%d)\n", __func__, SRC_PATH, n, width, height);

	grayscale_dither_ordered(width,height,data,processed_data);

	if (!stbi_write_png(DST_PATH, width, height, COMPONENT_GRAYSCALE, processed_data, PNG_STRIDE_IN_BYTES)) {
			fprintf(stderr, "[%s] export failed\n", __func__);
			exit(EXIT_FAILURE);
	}
	fprintf(stderr, "[%s] PNG file %s exported (%dx%d)\n", __func__, SRC_PATH, width, height);


  // free memory
  stbi_image_free(data);
  free(processed_data);
	return 0;
}
