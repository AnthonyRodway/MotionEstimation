#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_each_element(unsigned char *arr, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            printf("arr[%d][%d] = %d\n", j, i, *((arr+i*rows) + j));
        }
    }
}

void print_matrix(unsigned char *arr, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%4d ", *((arr+j*columns) + i));
        }
        printf("\n");
    }
}

void print_chunk(unsigned char arr[8][8], int x, int y) {
    unsigned char chunk[4][4];
    memset(chunk, 0, sizeof(chunk[0][0]) * 4 * 4);
    // memcpy(dest, src, sizeof (mytype) * rows * columns);
    for (int i = 0; i < 8; i++) {
        memcpy(chunk[i], arr[i], sizeof(unsigned char) * 4);
    }
    print_matrix(&chunk[0][0], 4, 4);
}

int main() {
    unsigned char arr[8][8];
    int ctr = 0;

    // memset(arr, 0, sizeof(arr[0][0]) * 8 * 8);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            arr[j][i] = ctr++;
        }
    }

    // print_each_element(arr, 8, 8);
    print_matrix(&arr[0][0], 8, 8);
    printf("\n");
    print_chunk(arr, 0, 0);

    return 0;
}