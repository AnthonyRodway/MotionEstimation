#include "sad.h"

int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE], int x, int y, int dx, int dy) {
    int diff, sad = 0;
    int i, j;

    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++){
            diff = (int) current_block[x + i][y + j] - (int) reference_block[(x + dx) + i][(y + dy) + j];
            
            // Get the absolute value
            if (diff < 0)
                sad -= diff;
            else
                sad += diff;
        }
    }
    
    return sad; // :(
}

void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
    int i, j = 0;
    for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
        memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
    }
}