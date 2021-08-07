#include <limits.h>
#include "bmp_parser.h"
#include "sad.h"

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
void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
    int i, j = 0;

    // Clear block
    memset(block, 0, sizeof(block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // Copy block from frame
    for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
        memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
    }
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
    for (y = 0; y < reference_frame_header.height; y++) {
        for (x = 0; x < reference_frame_header.width; x++) {
            // Reference frame
            blue = fgetc(reference_frame_fp);
            green = fgetc(reference_frame_fp);
            red = fgetc(reference_frame_fp);
            reference_frame_luminance[y][x] = get_luminance(red, green, blue);

            // Current frame
            blue = fgetc(current_frame_fp);
            green = fgetc(current_frame_fp);
            red = fgetc(current_frame_fp);
            current_frame_luminance[y][x] = get_luminance(red, green, blue);
        }
    }

    // Close the files
    fclose(reference_frame_fp);
    fclose(current_frame_fp);

    // declare local variables
    int temp_dx, temp_dy, temp_sad, dx, dy;
    unsigned int sad;

    // create blocks from the current and reference frames 
    unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE];
    memset(current_block, 0, sizeof(current_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE];
    memset(reference_block, 0, sizeof(reference_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // Create or open and overwrite the output file
    FILE *output_file;
    output_file = fopen("Motion Estimation Output.txt", "w");
    fprintf(output_file, "Block ( x-block, y-block ) -> ( x-displacement, y-displacement, SAD )\n");
    fprintf(output_file, "_____________________________________________________________________\n");

    // Iterate through each block in the reference frame
    for (y = 0; y < reference_frame_header.height; y += BLOCK_SIZE) {
        for (x = 0; x < reference_frame_header.width; x += BLOCK_SIZE) {
            temp_sad = INT_MAX;
            get_block(reference_frame_header.height, reference_frame_luminance, reference_block, x, y);

            // identical block
            temp_dx = 0;
            temp_dy = 0;
            get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
            sad = calculate_sad(reference_block, current_block);

            if (sad < temp_sad) {
                temp_sad = sad;
                dx = temp_dx;
                dy = temp_dy;
            }

            // up block
            if (temp_sad > 0 && y >= BLOCK_SIZE) {
                temp_dx = 0;
                temp_dy = -BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // up right block
            if (temp_sad > 0 && x < current_frame_header.width - BLOCK_SIZE && y >= BLOCK_SIZE) {
                temp_dx = BLOCK_SIZE;
                temp_dy = -BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // right block
            if (temp_sad > 0 && x < current_frame_header.width - BLOCK_SIZE) {
                temp_dy = 0;
                temp_dx = BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // down right block
            if (temp_sad > 0 && x < current_frame_header.width - BLOCK_SIZE && y < current_frame_header.height - BLOCK_SIZE) {
                temp_dx = BLOCK_SIZE;
                temp_dy = BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }
            
            // down block
            if (temp_sad > 0 && y < current_frame_header.height - BLOCK_SIZE) {
                temp_dx = 0;
                temp_dy = BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // down left block
            if (temp_sad > 0 && x >= BLOCK_SIZE && y < current_frame_header.height - BLOCK_SIZE) {
                temp_dx = -BLOCK_SIZE;
                temp_dy = BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // left block
            if (temp_sad > 0 && x >= BLOCK_SIZE) {
                temp_dy = 0;
                temp_dx = -BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // up left block
            if (temp_sad > 0 && x >= BLOCK_SIZE && y >= BLOCK_SIZE) {
                temp_dx = -BLOCK_SIZE;
                temp_dy = -BLOCK_SIZE;
                get_block(current_frame_header.height, current_frame_luminance, current_block, x+temp_dx, y+temp_dy);
                sad = calculate_sad(reference_block, current_block);

                if (sad < temp_sad) {
                    temp_sad = sad;
                    dx = temp_dx;
                    dy = temp_dy;
                }
            }

            // if either the x displacement or y displacement is non-zero
            if (dx != 0 || dy != 0) {
                printf("Block (%d, %d) -> (%d, %d, %d)\n", x >> BLOCK_SIZE_SHIFT, y >> BLOCK_SIZE_SHIFT, dx, dy, temp_sad ); 
                fprintf(output_file, "Block ( %7d, %7d ) -> ( %14d, %14d, %3d )\n", x >> BLOCK_SIZE_SHIFT, y >> BLOCK_SIZE_SHIFT, dx, dy, temp_sad );
            }
        }
    }

    // close the output file
    fclose(output_file);

    return 0;
}