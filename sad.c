#include "sad.h"
#include "test.h"

int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE], int x, int y, int dx, int dy) {
    // declare local variables
    int i, j, diff, sad = 0;
    
    // printf("SAD's perspective of reference block:\n");
    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, reference_block);
    // printf("SAD's perspective of current block:\n");
    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);

    // enter nested for loops to travers the 8x8 blocks 
    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++){
            // diff = (int) current_block[x + i][y + j] - (int) reference_block[(x + dx) + i][(y + dy) + j];
            diff = (int) current_block[i][j] - (int) reference_block[i][j];

            // Get the absolute value of diff and add it to SAD
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    }
    
    return sad; // :(
}

void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
    memset(block, 0, sizeof(block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);
    int i, j = 0;
    
    for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
        memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
    }
}