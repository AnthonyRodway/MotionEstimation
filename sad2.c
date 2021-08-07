#include "sad.h"

unsigned int calculate_sad_optimized_but_broken(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad;
    register unsigned int four_reference_pixels = 0;
    register unsigned int four_current_pixels = 0;
    register unsigned int x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // One register can hold 4 pixels, so we iterate x by 4
        for (x = 0; x < BLOCK_SIZE; x += 4) {
            // Copy four pixels from each block
            memcpy(four_reference_pixels, reference_block[y]+x, sizeof(unsigned char) * 4);
            memcpy(four_current_pixels, current_block[y]+x, sizeof(unsigned char) * 4);

            // __asm__("SAD %1, %2, %0" : "=r" (sad) : "r" (reference_pixel), "r" (current_pixel));
            diff = four_current_pixels[0] - four_reference_pixels[0];
            if (diff < 0)   sad -= diff;
            else            sad += diff;
            
            diff = four_current_pixels[1] - four_reference_pixels[1];
            if (diff < 0)   sad -= diff;
            else            sad += diff;
            
            diff = four_current_pixels[2] - four_reference_pixels[2];
            if (diff < 0)   sad -= diff;
            else            sad += diff;
            
            diff = four_current_pixels[3] - four_reference_pixels[3];
            if (diff < 0)   sad -= diff;
            else            sad += diff;
        }
    }
    return sad;
}
