#include "bmp_parser.h"

unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue){
    return ( ( 0.2126 * red ) + ( 0.7152 * green ) + ( 0.0722 * blue) );
}

void get_width_height(FILE *file, BITMAP_HEADER_INFORMATION *information){
    unsigned int length = 8; // lenth of bits needed for both width and height
    unsigned char data[length]; // array to hold the info

    // for the specific file passed, set the place you want to start seeking from 
    // in both cases width is found at 0x12 and height at 0x16 (8 bytes total from 0x12)
    fseek(file, 0x12, SEEK_SET);
    fread(data, sizeof(unsigned char), length, file);    

    // set all local variables and reset struct members that will be changed
    unsigned int temp = 0, i = 0;
    information->width = 0;
    information->height = 0;

    // two for loops to extract and add the data to the struct members
    // this for loop traverse through 0-3 (4 bytes) to get width
    for(i = 0; i < length/2; i++){
        temp = (unsigned int) data[i] << (i * 8);
        information->width += temp;
    }
    
    // this for loop traverse through 4-7 (4 bytes) to get height
    temp = 0;
    for(i = 4; i < length; i++){
        temp = (unsigned int) data[i] << (i * 8);
        information->height += temp;
    }

    //printf("\nwidth %i and height %i\n", information->width, information->height);
}