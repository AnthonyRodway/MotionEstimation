#include "sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register signed int diff;
    register unsigned int sad;
    register unsigned int reference_pixel, current_pixel;
    register unsigned int x, y;

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
        }
    }
    
    return sad;
}

void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
    memset(block, 0, sizeof(block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);
    int i, j = 0;
    for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
        memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
    }
}
