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
    int i, j = 0;
    memset(chunk, 0, sizeof(chunk[0][0]) * 4 * 4);
    for (i = 0, j = y; i < 4 && j < 8; i++, j++) {
        memcpy(chunk[i], arr[j]+x, sizeof(unsigned char) * 4);
    }
    print_matrix(&chunk[0][0], 4, 4);
}

int main() {
    unsigned char arr[8][8];
    int ctr = 0;
    int i, j = 0;

    // memset(arr, 0, sizeof(arr[0][0]) * 8 * 8);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            arr[j][i] = ctr++;
        }
    }

    // print_each_element(arr, 8, 8);
    print_matrix(&arr[0][0], 8, 8);
    printf("\n");

    for (i = 0; i < 8; i+=4) {
        for (j = 0; j < 8; j+=4) {
            print_chunk(arr, i, j);
            printf("\n");
        }
    }

    return 0;
}