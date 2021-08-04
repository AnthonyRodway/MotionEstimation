#include "test.h"

void print_matrix(int height, int width, unsigned char arr[height][width]) {
    int x, y;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            printf("%4d ", arr[y][x]);
        }
        printf("\n");
    }
}

void print_labelled_matrix_to_file(char *filename, int height, int width, unsigned char arr[height][width]) {
    int x, y;
    FILE *fp;

    fp = fopen(filename, "w");

    fprintf(fp, "\t  ");
    for (x = 0; x < width; x++) {
        fprintf(fp, "%4d ", x);
    }
    fprintf(fp, "\n\n");

    for (y = 0; y < height; y++) {
        fprintf(fp, "%4d  ", y);
        for (x = 0; x < width; x++) {
            fprintf(fp, "%4d ", arr[y][x]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}
