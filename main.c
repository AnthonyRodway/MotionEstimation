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
void sad_computation(int x, int y, int r, int s){
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
 * Function: get_luminance()
 * Parameters: (unsigned char) red   - the red component of the pixel
 *             (unsigned char) green - the green component of the pixel
 *             (unsigned char) blue  - the blue component of the pixel
 * Return: (unsigned char) - a char value with a value of the luminance of the pixel
 * Description: This functions perpose is to take the different components of the pixel
 *              and calculate a luminance value to return. This makes working with motion
 *              estimation easier.
 * Source: https://en.wikipedia.org/wiki/Relative_luminance 
 */
unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue){
    return ( ( 0.2126 * red ) + ( 0.7152 * green ) + ( 0.0722 * blue) );
}

/*
 * Function: main()
 * Parameters: (int) argc     - stores number of command-line arguments passed by the user including the name of the program
 *             (char) *argv[] - is array of character pointers listing all the arguments
 * Return: (int) - an int value indicating how the program exited. 0 = normal, 1 = abnormal (error)
 * Description: This function is the main workhorse of the program, it will do all of the
 *              argument handeling, image processing and SAD handelling. 
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

    // declare pointers of type FILE
    FILE *reference;
    FILE *current;

    return 0;
}