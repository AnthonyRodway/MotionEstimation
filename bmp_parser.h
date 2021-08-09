#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

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
    uint16_t type;
    uint32_t size;
    uint16_t reserved_1;
    uint16_t reserved_2;
    uint32_t offset;
    uint32_t width;
    uint32_t height;
} BitmapHeader;

/*
 * get_luminance
 * =============
 * Converts the red, green, and blue components of an RGB pixel into a relative luminance value.
 * 
 * red:   the red component of the pixel
 * green: the green component of the pixel
 * blue:  the blue component of the pixel
 * 
 * Returns the relative luminance value of the pixel
 * 
 * Reference(s): https://en.wikipedia.org/wiki/Relative_luminance 
 */
unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue);

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