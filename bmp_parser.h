#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

/*
 * Struct: Bitmap_Information
 * Parameters: (unsigned short) type            - The header field used to identify the BMP (2 bytes)
 *             (unsigned int) size              - The size of the BMP file in bytes (4 bytes)
 *             (unsigned short) reserved_1      - reserved section in the header (2 bytes)
 *             (unsigned short) reserved_2      - second reserved section in the header (2 bytes)
 *             (unsigned int) offset            - starting address, of the byte where the bitmap image data 
 *                                                (pixel array) can be found. (4 bytes)
 * Description: This structure holds all relevant information about the extracted bitmap info
 * Source: https://en.wikipedia.org/wiki/BMP_file_format
 */
typedef struct Bitmap_Information{
    unsigned short type;
    unsigned int size;
    unsigned short reserved_1;
    unsigned short reserved_2;
    unsigned int offset;
    unsigned int width;
    unsigned int height;
} BITMAP_HEADER_INFORMATION;

/*
 * Function: get_luminance()
 * Parameters: (unsigned char) red   - the red component of the pixel
 *             (unsigned char) green - the green component of the pixel
 *             (unsigned char) blue  - the blue component of the pixel
 * Return: (unsigned char) - a char value with a value of the luminance of the pixel
 * Description: This functions purpose is to take the different components of the pixel
 *              and calculate a luminance value to return. This makes working with motion
 *              estimation easier.
 * Source: https://en.wikipedia.org/wiki/Relative_luminance 
 */
unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue);

/*
 * Function: get_width_height()
 * Parameters: (FILE *) file                             - a reference to the specified file 
 *             (BITMAP_HEADER_INFORMATION *) information - a reference to the specified stuct
 * Return: (void) - no return
 * Description: This function
 */
void get_width_height(FILE *file, BITMAP_HEADER_INFORMATION *information);