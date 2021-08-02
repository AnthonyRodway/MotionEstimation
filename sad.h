#include <string.h>

#define BLOCK_SIZE 8

/*
 * Result
 * ============
 * Will hold 
 * 
 * x:       
 * y:       
 * sad: 
 */
struct Result {
    int x;
    int y;
    int sad;
} Result;

/*
 * calculate_sad
 * =============
 * Calculates the sum of absolute values (SAD) between two blocks of size BLOCK_SIZE
 * 
 * reference_block: the reference block being looked at
 * current_block: the current block being looked at
 * 
 * Return the sad of the two blocks.
 */
int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE]);

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

