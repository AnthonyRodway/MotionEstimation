#include <limits.h>
#include "bmp_parser.h"
#include "sad.h"
#include "test.h"

/*
 * get_luminance
 * =============
 * Converts the red, green, and blue components of an RGB pixel into a relative luminance value.
 * 
 * red:   the red component of the pixel
 * green: the green component of the pixel
 * blue:  the blue component of the pixel
 * 
 * Returns the relative luminance value of the pixel
 * 
 * Reference(s): https://en.wikipedia.org/wiki/Relative_luminance 
 */
unsigned char get_luminance(unsigned char red, unsigned char green, unsigned char blue) {
    return ( ( 0.2126 * red ) + ( 0.7152 * green ) + ( 0.0722 * blue) );
}

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

    print_bmp_header(reference_frame_filename, &reference_frame_header);
    print_bmp_header(current_frame_filename, &current_frame_header);

    // Initialize variables to hold pixel colour components as well as counters
    unsigned char red, green, blue = 0;
    unsigned int x, y;

    // Initialize arrays to hold luminance values of both frames
    unsigned char reference_frame_luminance[reference_frame_header.height][reference_frame_header.width];
    unsigned char current_frame_luminance[current_frame_header.height][current_frame_header.width]; 
   
    // need to set the starting spot for seeking to offset
    fseek(reference_frame_fp, reference_frame_header.offset, SEEK_SET);
    fseek(current_frame_fp, current_frame_header.offset, SEEK_SET);

    // Iterate through every pixel in both frames
    for (x = 0; x < reference_frame_header.height; x++) {
        for (y = 0; y < reference_frame_header.width; y++) {
            // Reference frame
            blue = fgetc(reference_frame_fp);
            green = fgetc(reference_frame_fp);
            red = fgetc(reference_frame_fp);
            reference_frame_luminance[x][y] = get_luminance(red, green, blue);

            // Current frame
            blue = fgetc(current_frame_fp);
            green = fgetc(current_frame_fp);
            red = fgetc(current_frame_fp);
            current_frame_luminance[x][y] = get_luminance(red, green, blue);
        }
    }

    // Close the files
    fclose(reference_frame_fp);
    fclose(current_frame_fp);

    // print_matrix(reference_frame_header.height, reference_frame_header.width, reference_frame_luminance);
    // print_matrix(current_frame_header.height, current_frame_header.width, current_frame_luminance);

    // declare local variables
    int i, j, temp_dx, temp_dy, dx, dy, temp_sad, sad, block_count = 0;

    // 
    unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE];
    memset(current_block, 0, sizeof(current_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE];
    memset(reference_block, 0, sizeof(reference_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // struct Result sad_results[reference_frame_header.height/BLOCK_SIZE][reference_frame_header.width/BLOCK_SIZE];

    // get_block(current_frame_header.height, current_frame_luminance, current_block, 0, current_frame_header.height-BLOCK_SIZE);
    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
    // printf("\n");

    FILE *output_file;
    output_file = fopen("Motion Estimation Output.txt", "w");
    fprintf(output_file, "Block ( x-block, y-block ) -> ( x-displacement, y-displacement, SAD )\n");
    fprintf(output_file, "_____________________________________________________________________\n");

    // Iterate through each block in the reference frame
    for (y = 0; y < reference_frame_header.height; y += BLOCK_SIZE) {
        for (x = 0; x < reference_frame_header.width; x += BLOCK_SIZE) {
            block_count++;
            temp_dx = 0;
            temp_dy = 0;
            sad = INT_MAX;
            get_block(reference_frame_header.height, reference_frame_luminance, reference_block, x, y);
            // printf("\n");
            // printf("Looking at Reference Block:\n");
            // print_matrix(BLOCK_SIZE, BLOCK_SIZE, reference_block);
            // printf("\n");

            // identical block
            get_block(current_frame_header.height, current_frame_luminance, current_block, x, y);
            // printf("Checking Current Block:\n");
            // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
            // printf("\n");
            temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
            if (temp_sad < sad) {
                sad = temp_sad;
                dx = temp_dx;
                dy = temp_dy;
            }

            // up block
            if (sad > 0 && y >= BLOCK_SIZE) {
                temp_dx = 0;
                for (i = -1; i >= -BLOCK_SIZE; i--) {
                    temp_dy = i;
                    get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                    // printf("Checking Current Block (up):\n");
                    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                    // printf("\n");
                    temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                    if (temp_sad < sad) {
                        sad = temp_sad;
                        dx = temp_dx;
                        dy = temp_dy;
                    }
                    if (sad == 0) break;
                }
            }

            // right block
            if (sad > 0 && x < current_frame_header.width - BLOCK_SIZE) {
                temp_dy = 0;
                for (i = 1; i <= BLOCK_SIZE; i++) {
                    temp_dx = i;
                    get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                    // printf("Checking Current Block (right):\n");
                    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                    // printf("\n");
                    temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                    if (temp_sad < sad) {
                        sad = temp_sad;
                        dx = temp_dx;
                        dy = temp_dy;
                    }
                    if (sad == 0) break;
                }
            }
            
            // down block
            if (sad > 0 && y < current_frame_header.height - BLOCK_SIZE) {
                temp_dx = 0;
                for (i = 1; i <= BLOCK_SIZE; i++) {
                    temp_dy = i;
                    get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                    // printf("Checking Current Block (down):\n");
                    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                    // printf("\n");
                    temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                    if (temp_sad < sad) {
                        sad = temp_sad;
                        dx = temp_dx;
                        dy = temp_dy;
                    }
                    if (sad == 0) break;
                }
            }

            // left block
            if (sad > 0 && x >= BLOCK_SIZE) {
                temp_dy = 0;
                for (i = -1; i >= -BLOCK_SIZE; i--) {
                    temp_dx = i;
                    get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                    // printf("Checking Current Block (left):\n");
                    // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                    // printf("\n");
                    temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                    if (temp_sad < sad) {
                        sad = temp_sad;
                        dx = temp_dx;
                        dy = temp_dy;
                    }
                    if (sad == 0) break;
                }
            }

            // up right block
            if (sad > 0 && x < current_frame_header.width - BLOCK_SIZE && y >= BLOCK_SIZE) {
                for (i = 1; i <= BLOCK_SIZE; i++) { // right
                    for (j = -1; j >= -BLOCK_SIZE; j--) { // up
                        temp_dx = i;
                        temp_dy = j;
                        get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                        // printf("Checking Current Block:\n");
                        // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                        // printf("\n");
                        temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                        if (temp_sad < sad) {
                            sad = temp_sad;
                            dx = temp_dx;
                            dy = temp_dy;
                        }
                        if (sad == 0) break;
                    }
                    if (sad == 0) break;
                }
            }

            // up left block
            if (sad > 0 && x >= BLOCK_SIZE && y >= BLOCK_SIZE) {
                for (i = -1; i >= -BLOCK_SIZE; i--) { // left
                    for (j = -1; j >= -BLOCK_SIZE; j--) { // up
                        temp_dx = i;
                        temp_dy = j;
                        get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                        // printf("Checking Current Block:\n");
                        // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                        // printf("\n");
                        temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                        if (temp_sad < sad) {
                            sad = temp_sad;
                            dx = temp_dx;
                            dy = temp_dy;
                        }
                        if (sad == 0) break;
                    }
                    if (sad == 0) break;
                }
            }

            // down right block
            if (sad > 0 && x < current_frame_header.width - BLOCK_SIZE && y < current_frame_header.height - BLOCK_SIZE) {
                for (i = 1; i <= BLOCK_SIZE; i++) { // right
                    for (j = 1; j <= BLOCK_SIZE; j++) { // down
                        temp_dx = i;
                        temp_dy = j;
                        get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                        // printf("Checking Current Block:\n");
                        // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                        // printf("\n");
                        temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                        if (temp_sad < sad) {
                            sad = temp_sad;
                            dx = temp_dx;
                            dy = temp_dy;
                        }
                        if (sad == 0) break;
                    }
                    if (sad == 0) break;
                }
            }

            // down left block
            if (sad > 0 && x >= BLOCK_SIZE && y < current_frame_header.height - BLOCK_SIZE) {
                for (i = -1; i >= -BLOCK_SIZE; i--) { // left
                    for (j = 1; j <= BLOCK_SIZE; j++) { // down
                        temp_dx = i;
                        temp_dy = j;
                        get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                        // printf("Checking Current Block:\n");
                        // print_matrix(BLOCK_SIZE, BLOCK_SIZE, current_block);
                        // printf("\n");
                        temp_sad = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
                        if (temp_sad < sad) {
                            sad = temp_sad;
                            dx = temp_dx;
                            dy = temp_dy;
                        }
                        if (sad == 0) break;
                    }
                    if (sad == 0) break;
                }
            }

            // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].x = dx;
            // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].y = dy;
            // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].sad = temp_sad;
            
            // printf("BLOCK %d, %d\n", x/BLOCK_SIZE, y/BLOCK_SIZE);
            // printf("Displacement: %d, %d\n", dx, dy);
            // printf("SAD: %d\n\n", temp_sad);

            if (dx != 0 || dy != 0) {
                //printf("Block (%d, %d) -> (%d, %d, %d)\n", x/BLOCK_SIZE, y/BLOCK_SIZE, dx, dy, temp_sad);
                fprintf(output_file, "Block ( %7d, %7d ) -> ( %14d, %14d, %3d )\n", x/BLOCK_SIZE, y/BLOCK_SIZE, dx, dy, temp_sad);
            }
        }
    }
    fclose(output_file);
    printf("Total number of blocks: %d\n", block_count);

    return 0;
}