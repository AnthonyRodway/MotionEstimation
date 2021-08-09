#include "../sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    uint32_t ref_pixel1, ref_pixel2, cur_pixel1, cur_pixel2;
    uint32_t sad1 = 0;
    uint32_t sad2 = 0;
    int32_t x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // Loop unrolling (two pixels per iteration)
        for (x = 0; x < BLOCK_SIZE; x+= 2) {
            // Pixel 1 (parallelizable with pixel 2)
            ref_pixel1 = (uint32_t) reference_block[y][x];
            cur_pixel1 = (uint32_t) current_block[y][x];
            __asm__("SAD %1, %2, %0" : "=r" (sad1) : "r" (ref_pixel1), "r" (cur_pixel1));
            
            // Pixel 2 (parallelizable with pixel 1)
            ref_pixel2 = (uint32_t) reference_block[y][x+1];
            cur_pixel2 = (uint32_t) current_block[y][x+1];
            __asm__("SAD %1, %2, %0" : "=r" (sad2) : "r" (ref_pixel2), "r" (cur_pixel2));
        }
    }

    return sad1 + sad2;
}