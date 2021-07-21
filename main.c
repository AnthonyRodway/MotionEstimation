#include "bmp_parser.h"

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

int main(int argc, char *argv[]) {
    // Argument validation
    if (argc != 3) {
        printf("[Error] Incorrect Number of Arguments.\n");
        printf("Make sure input is in the form: ./main [reference file] [current file].\n");
        return 1;
    }

    // Get file names from program arguments and open the files
    char *reference_frame_filename = argv[1];
    char *current_frame_filename = argv[2];

    FILE *reference_frame_fp;
    FILE *current_frame_fp;

    reference_frame_fp = fopen(reference_frame_filename, "rb");
    current_frame_fp = fopen(current_frame_filename, "rb");

    // File existence validation
    if (reference_frame_fp == NULL) {
        fprintf(stderr, "[Error] Failed to fopen %s.\n", reference_frame_filename);
        return 1;
    } 

    if (current_frame_fp == NULL) {
        fprintf(stderr, "[Error] Failed to fopen %s.\n", current_frame_filename);
        return 1;
    }

    // Get the bitmap headers for both of the files
    BitmapHeader reference_frame_header;
    BitmapHeader current_frame_header;

    fread(&reference_frame_header, sizeof(BitmapHeader), 1, reference_frame_fp);
    fread(&current_frame_header, sizeof(BitmapHeader), 1, current_frame_fp);

    // Verify the files are bmp type ("MB")
    if (reference_frame_header.type != 0x4D42) {
        fprintf(stderr, "[Error] %s is not a .bmp file.\n", reference_frame_filename);
        return 1;
    } 

    if (current_frame_header.type != 0x4D42) {
        fprintf(stderr, "[Error] %s is not a .bmp file.\n", current_frame_filename);
        return 1;
    }
    
    // Get the width and height of the reference frame and current frame
    get_width_height(reference_frame_fp, &reference_frame_header);
    get_width_height(current_frame_fp, &current_frame_header);

    print_bmp_header(&reference_frame_filename, &reference_frame_header);
    print_bmp_header(&current_frame_filename, &current_frame_header);

    // Initialize variables to hold pixel colour components as well as counters
    unsigned char red, green, blue = 0;
    unsigned int i, j;

    // Initialize arrays to hold luminance values of both frames
    unsigned char reference_frame_luminance[reference_frame_header.height][reference_frame_header.width];
    unsigned char current_frame_luminance[current_frame_header.height][current_frame_header.width];

    // need to set the starting spot for seeking to offset
    fseek(reference_frame_fp, reference_frame_header.offset, SEEK_SET);
    fseek(current_frame_fp, current_frame_header.offset, SEEK_SET);

    // Iterate through every pixel in both frames
    for (i = 0; i < reference_frame_header.height; i++) {
        for (j = 0; j < reference_frame_header.width; j++) {
            // Reference frame
            blue = fgetc(reference_frame_fp);
            green = fgetc(reference_frame_fp);
            red = fgetc(reference_frame_fp);
            fgetc(reference_frame_fp);
            reference_frame_luminance[i][j] = get_luminance(red, green, blue);
            //printf("%c ", reference_frame_luminance[i][j]);

            // Current frame
            blue = fgetc(current_frame_fp);
            green = fgetc(current_frame_fp);
            red = fgetc(current_frame_fp);
            fgetc(current_frame_fp);
            current_frame_luminance[i][j] = get_luminance(red, green, blue);
        }
        //printf("\n");
    }

    // Close the files
    fclose(reference_frame_fp);
    fclose(current_frame_fp);

    return 0;
}