#include "../sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    int diff1, diff2;
    int sad = 0;
    int sad1 = 0;
    int sad2 = 0;
    int x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // Loop unrolling (two pixels per iteration)
        for (x = 0; x < BLOCK_SIZE; x+= 2) {
            // Pixel 1 (parallelizable with pixel 2)
            diff1 = (int) current_block[y][x] - (int) reference_block[y][x];
            if (diff1 < 0)
                sad1 -= diff1;
            else
                sad1 += diff1;

            // Pixel 2 (parallelizable with pixel 1)
            diff2 = (int) current_block[y][x + 1] - (int) reference_block[y][x + 1];
            if (diff2 < 0)
                sad2 -= diff2;
            else
                sad2 += diff2;

            sad += sad1 + sad2;
        }
    }

    return sad;
}