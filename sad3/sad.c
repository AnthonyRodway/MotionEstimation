#include "../sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    // Register variables
    register signed int diff;
    register unsigned int sad = 0;
    register unsigned int four_reference_pixels = 0;
    register unsigned int four_current_pixels = 0;
    register unsigned int x, y;

    // Non-register variables
    int i;
    unsigned char cur_pixel = 0;
    unsigned char ref_pixel = 0;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // One register can hold 4 pixels, so we iterate x by 4
        for (x = 0; x < BLOCK_SIZE; x += 4) {
            // Copy four pixels from the reference block
            four_reference_pixels = 0;
            four_reference_pixels |= (reference_block[y][x] << 24);
            four_reference_pixels |= (reference_block[y][x+1] << 16);
            four_reference_pixels |= (reference_block[y][x+2] << 8);
            four_reference_pixels |= reference_block[y][x+3];

            // Copy four pixels from the current block
            four_current_pixels = 0;
            four_current_pixels |= (current_block[y][x] << 24);
            four_current_pixels |= (current_block[y][x+1] << 16);
            four_current_pixels |= (current_block[y][x+2] << 8);
            four_current_pixels |= current_block[y][x+3];
            
            // If the four pixels are identical, the SAD will be 0
            if (four_reference_pixels == four_current_pixels)
                continue;

            // Calculate the SAD between the four pairs of pixels
            for (i = 3; i >= 0; i--) {
                // Get the ith byte (pixel)
                ref_pixel = (four_reference_pixels >> (8*i)) & 0xff;
                cur_pixel = (four_current_pixels >> (8*i)) & 0xff;

                // Calculate the absolute value of the difference between the two pixels
                diff = cur_pixel - ref_pixel;
                if (diff < 0) 
                    sad -= diff;
                else
                    sad += diff;
            }
        }
    }
    return sad;
}
