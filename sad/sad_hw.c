#include "../sad.h"

uint32_t calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    uint32_t ref_pixel, cur_pixel;
    uint32_t sad = 0;
    uint32_t x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        for (x = 0; x < BLOCK_SIZE; x++) {
            ref_pixel = (uint32_t) reference_block[y][x];
            cur_pixel = (uint32_t) current_block[y][x];

            // Get the absolute value of the difference between the two pixels
            __asm__("SAD %1, %2, %0" : "=r" (sad) : "r" (ref_pixel), "r" (cur_pixel));
        }
    }
    
    return sad;
}
