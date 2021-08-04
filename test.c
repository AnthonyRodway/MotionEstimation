#include "test.h"

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