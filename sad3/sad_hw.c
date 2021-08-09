#include "../sad.h"

uint32_t calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    // Register variables
    register int32_t diff;
    register uint32_t sad = 0;
    register uint32_t four_reference_pixels = 0;
    register uint32_t four_current_pixels = 0;
    register uint32_t x, y;

    // Non-register variables
    int32_t i;
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

            // Calculate the SAD between the four pairs of pixels
            __asm__("SAD %1, %2, %0" : "=r" (sad) : "r" (four_reference_pixels), "r" (four_current_pixels));
        }
    }
    return sad;
}

 