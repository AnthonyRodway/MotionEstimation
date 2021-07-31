#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_each_element(unsigned char *arr, int rows, int columns);

void print_matrix(int height, int width, unsigned char arr[height][width]);

void get_chunk(unsigned char arr[8][8], unsigned char chunk[4][4], int x, int y);