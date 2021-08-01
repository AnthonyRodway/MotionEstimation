#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

/*
 * BitmapHeader
 * ============
 * Holds all relevant information about a bitmap file.
 * 
 * type:       identifies the file as a bitmap image (2 bytes)
 * size:       the size of the BMP file in bytes (4 bytes)
 * reserved_1: first reserved section in the header (2 bytes)
 * reserved_2: second reserved section in the header (2 bytes)
 * offset:     starting address of the byte where the bitmap image data can be found (4 bytes)
 * 
 * Reference: https://en.wikipedia.org/wiki/BMP_file_format
 */
typedef struct BitmapHeader {
    unsigned short type;
    unsigned int   size;
    unsigned short reserved_1;
    unsigned short reserved_2;
    unsigned int   offset;
    unsigned int   width;
    unsigned int   height;
} BitmapHeader;

/*
 * get_width_height
 * ================
 * Extracts the width and height of a bitmap file.
 *
 * file:   reference to the bitmap file 
 * header: reference to the bitmap header
 * 
 * No return value
 */
void get_width_height(FILE *file, BitmapHeader *header);

/*
 * print_bmp_header
 * ================
 * Prints a bitmap file header.
 *
 * filename: reference to the bitmap file name
 * header:   reference to the bitmap file header
 * 
 * No return value
 */
void print_bmp_header(char *filename, BitmapHeader *header);