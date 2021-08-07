#include "sad.h"

// loop unrolling (probably not viable)
unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    int diff, sad = 0;
    int x, y;

    for (y = 0; y < BLOCK_SIZE; y+= 2) {
        for (x = 0; x < BLOCK_SIZE; x+= 2) {
            diff = (int) current_block[y][x] - (int) reference_block[y][x];

            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;

            diff = (int) current_block[y][x + 1] - (int) reference_block[y][x + 1];

            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    
        for (x = 0; x < BLOCK_SIZE; x+= 2) {
            diff = (int) current_block[y + 1][x] - (int) reference_block[y + 1][x];

            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;

            diff = (int) current_block[y + 1][x + 1] - (int) reference_block[y + 1][x + 1];

            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    }

    return sad;
}