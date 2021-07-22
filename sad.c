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

// #include "sad.h"

// int calculate_sad(unsigned char reference_block[][FRAME_SIZE], unsigned char current_block[][FRAME_SIZE], int x, int y, int dx, int dy) {
//     int diff, sad = 0;
//     int i, j;

//     for (i = 0; i < BLOCK_SIZE; i++) {
//         for (j = 0; j < BLOCK_SIZE; j++){
//             diff = (int) current_block[x + i][y + j] - (int) reference_block[(x + dx) + i][(y + dy) + j];
            
//             // Get the absolute value
//             if (diff < 0)
//                 sad -= diff;
//             else
//                 sad += diff;
//         }
//     }
    
//     return sad; // :(
// }