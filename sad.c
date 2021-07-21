#define BLOCK_SIZE 8

int calculate_sad(unsigned char **reference_block, unsigned char **current_block, int x, int y, int dx, int dy) {
    int diff, sad = 0;
    int i, j;

    for (i = 0; i < BLOCK_SIZE; i++) {
        for (j = 0; j < BLOCK_SIZE; j++){
            diff = (int) current_block[x + i][y + j] - (int) reference_block[(x + dx) + i][(y + dy) + j];
            
            // Get the absolute value
            if (diff < 0)
                diff -= diff;
            else
                sad += diff;
        }
    }
    
    return sad; // :(
}