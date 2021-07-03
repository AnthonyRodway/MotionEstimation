#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*
 * function: sadComputation()
 * parameters: (x, y) position of current block
 *             (r, s) motion vector(displacement of current block relative to reference block)
 * return: none
 * description: according to software solution 1 right now, bound to change...
 * 
 */
void sadComputation(int x, int y, int r, int s){
    int currentBlock[16][16], referenceBlock[16][16];
    int difference, sumAbsoluteDifferece = 0;
    int i, j;

    for(i = 0; i < 16; i++){
        for(j = 0; j < 16; j++){
            difference = currentBlock[x - i][y + j] - referenceBlock[(x + r) + i][(y + s) + j];
            
            // get the absolute value
            if(difference < 0){
                difference -= difference;
            }
            sumAbsoluteDifferece += difference;
        }
    }
}

/*
 * function: main()
 * parameters: argc - the number of arguments (including ./main)
 *             *argv[] - array of strings (character pointers) representing the individual arguments provided on the command line
 * return: none
 * description: main function
 * 
 */
int main(int argc, char *argv[]){
    // add some argument error checking
    if(argc != 3){
        printf("[Error] Incorrect Number of Arguments.\n");
        return 1;
    }

    char* filenameCurrent = argv[1];
    char* filenameReference = argv[2];

    printf("%s, %s\n", filenameCurrent, filenameReference);

    return 0;
}