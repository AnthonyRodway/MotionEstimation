#include "bmp_parser.h"

unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue) {
    return ( ( 0.2126 * red ) + ( 0.7152 * green ) + ( 0.0722 * blue) );
}

void get_width_height(FILE *file, BitmapHeader *header) {
    unsigned int LENGTH = 8;    // Number of bits needed for both width and height
    unsigned char data[LENGTH]; // Array to hold the header information

    // For the specified file, set the place we want to start seeking from 
    // In both cases, width is found at 0x12 and height at 0x16 (8 bytes total from 0x12)
    fseek(file, 0x12, SEEK_SET);
    fread(data, sizeof(unsigned char), LENGTH, file);    

    // Initialize all local variables and clear struct members that will be changed
    unsigned int temp = 0, i = 0;
    header->width = 0;
    header->height = 0;

    // Traverse through bytes 0-3 to get the width
    for(i = 0; i < LENGTH/2; i++){
        temp = (unsigned int) data[i] << (i * 8);
        header->width += temp;
    }
    
    // Traverse through bytes 4-7 to get the height
    temp = 0;
    for(i = 4; i < LENGTH; i++){
        temp = (unsigned int) data[i] << (i * 8);
        header->height += temp;
    }
}

void print_bmp_header(char *filename, BitmapHeader *header) {
    printf("%s\ntype: %i\nsize: %i\nres1: %i\nres2: %i\noffset: %i\nwidth: %i\nheight: %i\n\n",
        filename,
        header->type,
        header->size,
        header->reserved_1,
        header->reserved_2,
        header->offset,
        header->width,
        header->height
        );
}