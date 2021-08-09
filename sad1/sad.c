#include "../sad.h"

uint32_t calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    int32_t diff1, diff2;
    uint32_t sad1 = 0;
    uint32_t sad2 = 0;
    int32_t x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // Loop unrolling (two pixels per iteration)
        for (x = 0; x < BLOCK_SIZE-1; x += 2) {
            // Pixel 1 (parallelizable with pixel 2)
            diff1 = (int32_t) current_block[y][x] - (int32_t) reference_block[y][x];
            if (diff1 < 0)
                sad1 -= diff1;
            else
                sad1 += diff1;

            // Pixel 2 (parallelizable with pixel 1)
            diff2 = (int32_t) current_block[y][x + 1] - (int32_t) reference_block[y][x + 1];
            if (diff2 < 0)
                sad2 -= diff2;
            else
                sad2 += diff2;

            
        }
    }

    return sad1 + sad2;
}