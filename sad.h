#include <string.h>

#define BLOCK_SIZE 8
#define BLOCK_SIZE_SHIFT 3

/*
 * calculate_sad
 * =============
 * Calculates the sum of absolute values (SAD) between two blocks of size BLOCK_SIZE
 * 
 * reference_block: the reference block
 * current_block:   the current block      
 * 
 * Returns the SAD
 */
unsigned int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]);

// broken, will eventually replace calculate_sad
unsigned int calculate_sad_optimized_but_broken(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]);

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
 * No return value
 */
void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y);
