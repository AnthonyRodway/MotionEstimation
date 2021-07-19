#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

/*
 * Struct: Bitmap_Information
 * Parameters: (unsigned short) type            - The header field used to identify the BMP (2 bytes)
 *             (unsigned int) size              - The size of the BMP file in bytes (4 bytes)
 *             (unsigned short) reserved_1      - reserved section in the header (2 bytes)
 *             (unsigned short) reserved_2      - second reserved section in the header (2 bytes)
 *             (unsigned int) offset            - starting address, of the byte where the bitmap image data 
 *                                                (pixel array) can be found. (4 bytes)
 * Description: This structure holds all relevant information about the extracted bitmap info
 * Source: https://en.wikipedia.org/wiki/BMP_file_format
 */
typedef struct Bitmap_Information{
    unsigned short type;
    unsigned int size;
    unsigned short reserved_1;
    unsigned short reserved_2;
    unsigned int offset;
    unsigned int width;
    unsigned int height;
} BITMAP_HEADER_INFORMATION;

/*
 * Function: get_luminance()
 * Parameters: (unsigned char) red   - the red component of the pixel
 *             (unsigned char) green - the green component of the pixel
 *             (unsigned char) blue  - the blue component of the pixel
 * Return: (unsigned char) - a char value with a value of the luminance of the pixel
 * Description: This functions purpose is to take the different components of the pixel
 *              and calculate a luminance value to return. This makes working with motion
 *              estimation easier.
 * Source: https://en.wikipedia.org/wiki/Relative_luminance 
 */
unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue){
    return ( ( 0.2126 * red ) + ( 0.7152 * green ) + ( 0.0722 * blue) );
}

/*
 * Function: get_width_height()
 * Parameters: (FILE *) file                             - a reference to the specified file 
 *             (BITMAP_HEADER_INFORMATION *) information - a reference to the specified stuct
 * Return: (void) - no return
 * Description: This function
 */
void get_width_height(FILE *file, BITMAP_HEADER_INFORMATION *information){
    unsigned int length = 8; // lenth of bits needed for both width and height
    unsigned char data[length]; // array to hold the info

    // for the specific file passed, set the place you want to start seeking from 
    // in both cases width is found at 0x12 and height at 0x16 (8 bytes total from 0x12)
    fseek(file, 0x12, SEEK_SET);
    fread(data, sizeof(unsigned char), length, file);    

    // set all local variables and reset struct members that will be changed
    unsigned int temp = 0, i = 0;
    information->width = 0;
    information->height = 0;

    // two for loops to extract and add the data to the struct members
    // this for loop traverse through 0-3 (4 bytes) to get width
    for(i = 0; i < length/2; i++){
        temp = (unsigned int) data[i] << (i * 8);
        information->width += temp;
    }
    
    // this for loop traverse through 4-7 (4 bytes) to get height
    temp = 0;
    for(i = 4; i < length; i++){
        temp = (unsigned int) data[i] << (i * 8);
        information->height += temp;
    }

    //printf("\nwidth %i and height %i\n", information->width, information->height);
}

/*
 * Function: sadComputation()
 * Parameters: (x, y) position of current block
 *             (r, s) motion vector(displacement of current block relative to reference block)
 * Return: none
 * Description: according to software solution 1 right now, bound to change...
 */
// void sad_computation(int x, int y, int r, int s){
//     int currentBlock[16][16], referenceBlock[16][16];
//     int difference, sumAbsoluteDifferece = 0;
//     int i, j;

//     for(i = 0; i < 16; i++){
//         for(j = 0; j < 16; j++){
//             difference = currentBlock[x - i][y + j] - referenceBlock[(x + r) + i][(y + s) + j];
            
//             // get the absolute value
//             if(difference < 0){
//                 difference -= difference;
//             }
//             sumAbsoluteDifferece += difference;
//         }
//     }
// }


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
        printf("Make sure input is in the form: ./main [reference file] [current file].\n");
        return 1;
    }

    // get file names
    char *reference_filename = argv[1];
    char *current_filename = argv[2];

    // declare pointers of type FILE and open the files
    FILE *reference_file;
    FILE *current_file;

    // open the files
    reference_file = fopen(reference_filename, "rb");
    current_file = fopen(current_filename, "rb");

    // test to make sure the files exist
    if (reference_file == NULL){
        fprintf(stderr, "[Error] Failed to fopen %s.\n", reference_filename);
        return 1;
    } 

    if (current_file == NULL){
        fprintf(stderr, "[Error] Failed to fopen %s.\n", current_filename);
        return 1;
    }

    // get the bitmap headers for both of the files
    BITMAP_HEADER_INFORMATION reference_header;
    BITMAP_HEADER_INFORMATION current_header;

    // pull bitmap header info from the files
    fread(&reference_header, sizeof(BITMAP_HEADER_INFORMATION), 1, reference_file);
    fread(&current_header, sizeof(BITMAP_HEADER_INFORMATION), 1, current_file);

    // test to make sure the files are .bmp ("MB")
    if (reference_header.type != 0x4D42){
        fprintf(stderr, "[Error] %s is not a .bmp file.\n", reference_filename);
        return 1;
    } 

    if (current_header.type != 0x4D42){
        fprintf(stderr, "[Error] %s is not a .bmp file.\n", current_filename);
        return 1;
    }
    
    // call get_width_height function to populate the structs with width and height too
    get_width_height(reference_file, &reference_header);
    get_width_height(current_file, &current_header);

    printf("%s\ntype: %i\nsize: %i\nres1: %i\nres2: %i\noffset: %i\nwidth: %i\nheight: %i\n", reference_filename, reference_header.type, reference_header.size, reference_header.reserved_1, reference_header.reserved_2, reference_header.offset, reference_header.width, reference_header.height);
    printf("\n");
    printf("%s\ntype: %i\nsize: %i\nres1: %i\nres2: %i\noffset: %i\nwidth: %i\nheight: %i\n", current_filename, current_header.type, current_header.size, current_header.reserved_1, current_header.reserved_2, current_header.offset, current_header.width, current_header.height);

    // initialize colour and other local variables needed
    unsigned char red, green, blue = 0;
    unsigned int i, j;

    // initialized luminance arrays for rgb to luminance conversion
    unsigned char reference_luminance[reference_header.height][reference_header.width];
    unsigned char current_luminance[current_header.height][current_header.width];

    // need to set the starting spot for seeking to offset
    fseek(reference_file, reference_header.offset, SEEK_SET);
    fseek(current_file, current_header.offset, SEEK_SET);

    // nested for loop to go through every pixel on the image
    for(i = 0; i < reference_header.height; i++){
        for(j = 0; j < reference_header.width; j++){
            // reference image
            blue = fgetc(reference_file);
            green = fgetc(reference_file);
            red = fgetc(reference_file);
            fgetc(reference_file);
            reference_luminance[i][j] = get_luminance(red, green, blue);
            //printf("%c ", reference_luminance[i][j]);

            // current image
            blue = fgetc(current_file);
            green = fgetc(current_file);
            red = fgetc(current_file);
            fgetc(current_file);
            current_luminance[i][j] = get_luminance(red, green, blue);
        }
        //printf("\n");
    }

    // close the files
    fclose(reference_file);
    fclose(current_file);

    // start of the SAD algorithm


    return 0;
}