#include <string.h>

#define BLOCK_SIZE 8
#define BLOCK_SIZE_SHIFT 3

/*
 * calculate_sad
 * =============
 * Calculates the sum of absolute values (SAD) between two blocks of size BLOCK_SIZE
 * 
 * frame_size: the size of the frame 
 * frame:      the frame
 * block:      a block to store the result
 * x:          the x position of the current block
 * y:          the y position of the current block
 * 
 * No return value.
 */
int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE], int x, int y, int dx, int dy);

/*
 * get_block
 * =============
 * Gets a block of size {BLOCK_SIZE} from a frame, starting at provided coordinates.
 * 
 * frame_size: the size of the frame 
 * frame:      the frame
 * block:      a block to store the result
 * x:          the x value to start from
 * y:          the y value to start from
 * 
 * No return value.
 */
void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y);
