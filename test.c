#include "test.h"
// #include <math.h>
// #define BLOCK_SIZE 4

void print_each_element(unsigned char *arr, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            printf("arr[%d][%d] = %d\n", j, i, *((arr+i*rows) + j));
        }
    }
}

void print_matrix(int height, int width, unsigned char arr[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%4d ", arr[i][j]);
        }
        printf("\n");
    }
}

// void get_chunk(unsigned char arr[8][8], unsigned char chunk[4][4], int x, int y) {
//     int i, j = 0;
//     for (i = 0, j = y; i < 4 && j < 8; i++, j++) {
//         memcpy(chunk[i], arr[j]+x, sizeof(unsigned char) * 4);
//     }
// }

// void get_block(int frame_size, unsigned char frame[frame_size][frame_size], unsigned char block[BLOCK_SIZE][BLOCK_SIZE], int x, int y) {
//     memset(block, 0, sizeof(block[0][0]) * BLOCK_SIZE * BLOCK_SIZE);
//     int i, j = 0;
//     for (i = 0, j = y; i < BLOCK_SIZE && j < frame_size; i++, j++) {
//         memcpy(block[i], frame[j]+x, sizeof(unsigned char) * BLOCK_SIZE);
//     }
// }

// int main() {
//     int frame_size = 16;
//     int arr[frame_size][frame_size];
//     int ctr = 0;
//     int i, j = 0;
//     int x, y = 0;

//     // memset(arr, 0, sizeof(arr[0][0]) * 8 * 8);

//     for (i = 0; i < frame_size; i++) {
//         for (j = 0; j < frame_size; j++) {
//             arr[j][i] = ctr++;
//         }
//     }

//     // print_each_element(arr, 8, 8);
//     print_matrix(frame_size, frame_size, arr);
//     printf("\n");

//     int block[BLOCK_SIZE][BLOCK_SIZE];

//     for (x = max(0, i-1); i < 8; i+=4) {
//         for (j = 0; j < 8; j+=4) {
//             get_block(frame_size, arr, block, 4, 4);
//             print_matrix(frame
//             printf("\n");
//         }
//     }

//     return 0;
// }