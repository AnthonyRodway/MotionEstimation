#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char *argv[]){
    // add some argument error checking
    if(argc != 3){
        printf("[Error] Incorrect Number of Arguments.\n");
        return 1;
    }
    printf("hello");

    return 0;
}