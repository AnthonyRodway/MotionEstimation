#!/bin/bash

for (( i=0; i<=3; i++ ))
do
    if [ $i -eq 0 ]
    then
        cd "sad"
    else
        cd "sad$i"
    fi

    mkdir 1
    echo "Command used to compile: \`gcc ...\`" > "README.md"
    gcc ../main.c ../bmp_parser.c sad.c -o ./1/sad.exe

    mkdir 3
    echo "Command used to compile: \`gcc -O0 ...\`" > "README.md"
    gcc -O0 ../main.c ../bmp_parser.c sad.c -o ./3/sad.exe

    mkdir 4
    echo "Command used to compile: \`gcc -O1 ...\`" > "README.md"
    gcc -O1 ../main.c ../bmp_parser.c sad.c -o ./4/sad.exe

    mkdir 5
    echo "Command used to compile: \`gcc -O2 ...\`" > "README.md"
    gcc -O2 ../main.c ../bmp_parser.c sad.c -o ./5/sad.exe

    mkdir 6
    echo "Command used to compile: \`gcc -O3 ...\`" > "README.md"
    gcc -O3 ../main.c ../bmp_parser.c sad.c -o ./6/sad.exe

    mkdir 7
    echo "Command used to compile: \`gcc -Os ...\`" > "README.md"
    gcc -Os ../main.c ../bmp_parser.c sad.c -o ./7/sad.exe

    cd ..
done
