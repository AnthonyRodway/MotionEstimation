#include "../sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad;
    register unsigned int reference_pixel, current_pixel;
    register unsigned int x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        for (x = 0; x < BLOCK_SIZE; x++) {
            reference_pixel = reference_block[y][x];
            current_pixel = current_block[y][x];

            // Get the absolute value of the difference between the two pixels
            diff = current_pixel - reference_pixel;
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;

            
        }
    }
    return sad;
}