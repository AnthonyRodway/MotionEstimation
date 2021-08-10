#!/bin/bash

cd $1

for (( j=1; j<=7; j++ ))
do
    if [ $j -eq 2 ]
    then
        continue
    else
        cd $j

        valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./sad.exe ../../testing/frame1.bmp ../../testing/frame2.bmp
        callgrind_annotate callgrind.out > callgrind.txt

        valgrind --tool=cachegrind --cachegrind-out-file=cachegrind.out --log-file=cachegrind.txt --branch-sim=yes ./sad.exe ../../testing/frame1.bmp ../../testing/frame2.bmp

        perf record ./sad.exe ../../testing/frame1.bmp ../../testing/frame2.bmp

        (time ./sad.exe ../../testing/frame1.bmp ../../testing/frame2.bmp) 2> time.txt

        cd ..
    fi
done

cd ..
