#include <limits.h>
#include "bmp_parser.h"
#include "sad.h"
#include "test.h"

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
        // printf("\n");
    }

    // Close the files
    fclose(reference_frame_fp);
    fclose(current_frame_fp);

    // for (int i = 0; i < reference_frame_header.height; i++) {
    //     for (int j = 0; j < reference_frame_header.width; j++) {
    //         printf("%4d ", reference_frame_luminance[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = reference_frame_header.height-1; i >= 0; i--) {
    //     for (int j = 0; j < reference_frame_header.width; j++) {
    //         printf("%4d ", reference_frame_luminance[i][j]);
    //     }
    //     printf("\n");
    // }

    print_matrix(reference_frame_header.height, reference_frame_header.width, reference_frame_luminance);

    // int temp_dx, temp_dy, dx, dy, temp = 0;
    // int temp_sad;
    
    // int block_height = reference_frame_header.height/BLOCK_SIZE;
    // int block_width = reference_frame_header.width/BLOCK_SIZE;

    // unsigned char current_block[BLOCK_SIZE][BLOCK_SIZE];
    // memset(current_block, 0, sizeof(current_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // unsigned char reference_block[BLOCK_SIZE][BLOCK_SIZE];
    // memset(reference_block, 0, sizeof(reference_block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);

    // struct Result sad[block_height][block_width];

    // // Iterate through each block in the current frame
    // int ctr = 0;
    // for (y = current_frame_header.height-1; y >= 0; y -= BLOCK_SIZE) {
    //     for (x = 0; x < current_frame_header.width; x += BLOCK_SIZE) {
    //         ctr++;
    //         temp_sad = INT_MAX;
    //         // printf("current x, y = %d, %d\n", x, y);
    //         get_block(current_frame_header.height, current_frame_luminance, current_block, x, y);
            
    //         // identical block
    //         temp_dx = 0;
    //         temp_dy = 0;
    //         get_block(reference_frame_header.height, reference_frame_luminance, reference_block, temp_dx, temp_dy);
    //         temp = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
    //         if (temp < temp_sad) {
    //             temp_sad = temp;
    //             dx = temp_dx;
    //             dy = temp_dy;
    //         }

    //         // up
    //         if (temp_sad > 0 && y >= BLOCK_SIZE) {
    //             temp_dx = 0;
    //             temp_dy = -BLOCK_SIZE;
    //             get_block(reference_frame_header.height, reference_frame_luminance, reference_block, temp_dx, temp_dy);
    //             temp = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
    //             if (temp < temp_sad) {
    //                 temp_sad = temp;
    //                 dx = temp_dx;
    //                 dy = temp_dy;
    //             }
    //         }

    //         // right
    //         if (temp_sad > 0 && x <= block_width - BLOCK_SIZE) {
    //             temp_dx = BLOCK_SIZE;
    //             temp_dy = 0;
    //             get_block(reference_frame_header.height, reference_frame_luminance, reference_block, temp_dx, temp_dy);
    //             temp = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
    //             if (temp < temp_sad) {
    //                 temp_sad = temp;
    //                 dx = temp_dx;
    //                 dy = temp_dy;
    //             }
    //         }
            
    //         // down
    //         if (temp_sad > 0 && y <= block_height - BLOCK_SIZE) {
    //             temp_dx = 0;
    //             temp_dy = BLOCK_SIZE;
    //             get_block(reference_frame_header.height, reference_frame_luminance, reference_block, temp_dx, temp_dy);
    //             temp = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
    //             if (temp < temp_sad) {
    //                 temp_sad = temp;
    //                 dx = temp_dx;
    //                 dy = temp_dy;
    //             }
    //         }

    //         // left
    //         if (temp_sad > 0 && x >= BLOCK_SIZE) {
    //             temp_dx = -BLOCK_SIZE;
    //             temp_dy = 0;
    //             get_block(reference_frame_header.height, reference_frame_luminance, reference_block, temp_dx, temp_dy);
    //             temp = calculate_sad(reference_block, current_block, x, y, temp_dx, temp_dy);
    //             if (temp < temp_sad) {
    //                 temp_sad = temp;
    //                 dx = temp_dx;
    //                 dy = temp_dy;
    //             }
    //         }

    //         // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].x = dx;
    //         // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].y = dy;
    //         // sad[y/BLOCK_SIZE][x/BLOCK_SIZE].sad = temp_sad;
            
    //         // printf("BLOCK %d, %d\n", x/BLOCK_SIZE, y/BLOCK_SIZE);
    //         // printf("Displacement: %d, %d\n", dx, dy);
    //         // printf("SAD: %d\n\n", temp_sad);

    //         if (dx != 0 || dy != 0) {
    //             printf("Block (%d, %d) -> (%d, %d, %d)\n", x/BLOCK_SIZE, y/BLOCK_SIZE, dx, dy, temp_sad ); 
    //         }
    //     }
    // }
    // printf("Total number of blocks: %d\n", ctr);

    return 0;
}