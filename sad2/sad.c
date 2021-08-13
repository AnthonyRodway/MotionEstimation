#include "../sad.h"

uint32_t calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    register int32_t diff;
    register uint32_t sad = 0;
    register uint32_t reference_pixel, current_pixel;
    register uint32_t x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        for (x = 0; x < BLOCK_SIZE; x++) {
            reference_pixel = (uint32_t) reference_block[y][x];
            current_pixel = (uint32_t) current_block[y][x];

            // Get the absolute value of the difference between the two pixels
            diff = current_pixel - reference_pixel;
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    }
    return sad;
}
