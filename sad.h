#define BLOCK_SIZE 8

/*
 * Function: sadComputation()
 * Parameters: (x, y) position of current block
 *             (r, s) motion vector(displacement of current block relative to reference block)
 * Return: none
 * Description: according to software solution 1 right now, bound to change...
 */
int calculate_sad(unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE], unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE], int x, int y, int dx, int dy);

struct Result {
    int x;
    int y;
    int sad;
} Result;