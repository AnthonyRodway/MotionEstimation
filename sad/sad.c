#include "../sad.h"

unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]) {
    int diff, sad = 0;
    int x, y;

    // Iterate over each pixel in both blocks
    for (y = 0; y < BLOCK_SIZE; y++) {
        for (x = 0; x < BLOCK_SIZE; x++) {
            // Get the absolute value of the difference between the two pixels
            diff = (int) current_block[y][x] - (int) reference_block[y][x];
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    }
    
    return sad;
}
