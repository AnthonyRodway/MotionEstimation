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
    echo "Command used to compile: \`arm-linux-gcc -static ...\`" > "README.md"
    arm-linux-gcc -static -S sad.c -o ./1/sad.s
    arm-linux-gcc -static -S sad_hw.c -o ./1/sad_hw.s
    arm-linux-gcc -static ../main.c ../bmp_parser.c sad.c -o ./1/sad.exe

    mkdir 2
    echo "Command used to compile: \`arm-linux-gcc -static -march=armv5 ...\`" > "README.md"
    arm-linux-gcc -static -march=armv5 -S sad.c -o ./2/sad.s
    arm-linux-gcc -static -march=armv5 -S sad_hw.c -o ./2/sad_hw.s
    arm-linux-gcc -static -march=armv5 ../main.c ../bmp_parser.c sad.c -o ./2/sad.exe

    mkdir 3
    echo "Command used to compile: \`arm-linux-gcc -static -marm -O0 ...\`" > "README.md"
    arm-linux-gcc -static -marm -O0 -S sad.c -o ./3/sad.s
    arm-linux-gcc -static -marm -O0 -S sad_hw.c -o ./3/sad_hw.s
    arm-linux-gcc -static -marm -O0 ../main.c ../bmp_parser.c sad.c -o ./3/sad.exe

    mkdir 4
    echo "Command used to compile: \`arm-linux-gcc -static -marm -O1 ...\`" > "README.md"
    arm-linux-gcc -static -marm -O1 -S sad.c -o ./4/sad.s
    arm-linux-gcc -static -marm -O1 -S sad_hw.c -o ./4/sad_hw.s
    arm-linux-gcc -static -marm -O1 ../main.c ../bmp_parser.c sad.c -o ./4/sad.exe

    mkdir 5
    echo "Command used to compile: \`arm-linux-gcc -static -marm -O2 ...\`" > "README.md"
    arm-linux-gcc -static -marm -O2 -S sad.c -o ./5/sad.s
    arm-linux-gcc -static -marm -O2 -S sad_hw.c -o ./5/sad_hw.s
    arm-linux-gcc -static -marm -O2 ../main.c ../bmp_parser.c sad.c -o ./5/sad.exe

    mkdir 6
    echo "Command used to compile: \`arm-linux-gcc -static -marm -O3 ...\`" > "README.md"
    arm-linux-gcc -static -marm -O3 -S sad.c -o ./6/sad.s
    arm-linux-gcc -static -marm -O3 -S sad_hw.c -o ./6/sad_hw.s
    arm-linux-gcc -static -marm -O3 ../main.c ../bmp_parser.c sad.c -o ./6/sad.exe

    mkdir 7
    echo "Command used to compile: \`arm-linux-gcc -static -marm -Os ...\`" > "README.md"
    arm-linux-gcc -static -marm -Os -S sad.c -o ./7/sad.s
    arm-linux-gcc -static -marm -Os -S sad_hw.c -o ./7/sad_hw.s
    arm-linux-gcc -static -marm -Os ../main.c ../bmp_parser.c sad.c -o ./7/sad.exe

    cd ..
done
