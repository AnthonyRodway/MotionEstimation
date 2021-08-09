#include "../sad.h"

uint32_t calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    // Register variables
    register int32_t diff;
    register uint32_t sad = 0;
    register uint32_t x, y;

    // Non-register variables
    int32_t i, temp;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        // One register can hold 4 pixels, so we iterate x by 4
        for (x = 0; x < BLOCK_SIZE; x += 4) {
            // Calculate the SAD between the four pairs of pixels
            diff = 0;
            diff |= ((current_block[y][x] << 24) - (reference_block[y][x] << 24)) << 24;
            diff |= ((current_block[y][x] << 16) - (reference_block[y][x] << 16)) << 16;
            diff |= ((current_block[y][x] << 8) - (reference_block[y][x] << 8)) << 8;
            diff |= current_block[y][x] - reference_block[y][x];
            
            for (i = 3; i >= 0; i--) {
                // Get the ith byte (pixel)
                temp = (diff >> (8*i)) & 0xff;
                if (temp < 0) 
                    sad -= temp;
                else
                    sad += temp;
            }
        }
    }
    return sad;
}


 