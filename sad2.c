#include "sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad = 0;
    register unsigned int four_reference_pixels = 0;
    register unsigned int four_current_pixels = 0;
    register unsigned int x, y;
    unsigned char cur_pixel = 0;
    unsigned char ref_pixel = 0;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // One register can hold 4 pixels, so we iterate x by 4
        for (x = 0; x < BLOCK_SIZE; x += 4) {
            // Copy four pixels from each block
            four_reference_pixels |= (reference_block[y][x] << 24);
            four_reference_pixels |= (reference_block[y][x+1] << 16);
            four_reference_pixels |= (reference_block[y][x+2] << 8);
            four_reference_pixels |= reference_block[y][x+3];

            four_current_pixels |= (current_block[y][x] << 24);
            four_current_pixels |= (current_block[y][x+1] << 16);
            four_current_pixels |= (current_block[y][x+2] << 8);
            four_current_pixels |= current_block[y][x+3];

            if (four_reference_pixels == 0 && four_current_pixels == 0) continue;

            // __asm__("SAD %1, %2, %0" : "=r" (sad) : "r" (reference_pixel), "r" (current_pixel));
            for (int i = 3; i >= 0; i--) {
                ref_pixel = (four_reference_pixels >> (8*i)) & 0xff;
                cur_pixel = (four_current_pixels >> (8*i)) & 0xff;

                diff = cur_pixel - ref_pixel;
                if (diff < 0) sad -= diff;
                else          sad += diff;
            }
        }
    }
    return sad;
}
