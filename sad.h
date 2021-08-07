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
