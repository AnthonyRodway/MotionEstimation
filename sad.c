#include "sad.h"

unsigned int calculate_sad_optimized_but_broken(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad;
    register unsigned char four_reference_pixels[4], four_current_pixels[4];
    register unsigned int x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < 8; y++) {
        // One register can hold 4 pixels, so we iterate x by 4
        for (x = 0; x < 8; x += 4) {
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

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad;
    register unsigned int reference_pixel, current_pixel;
    register unsigned int x, y;

    // Enter the nested loops to traverse the 8x8 blocks 
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            reference_pixel = reference_block[y][x];
            current_pixel = current_block[y][x];

            diff = current_pixel - reference_pixel;

            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;

            // __asm__("SAD %1, %2, %0" : "=r" (sad) : "r" (reference_pixel), "r" (current_pixel));
        }
    }
    
    return sad;
}

void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
    int i, j = 0;

    // Clear block
    memset(block, 0, sizeof(block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // Copy block from frame
    for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
        memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
    }
}
