#!/bin/bash

cd $1

for (( j=1; j<=7; j++ ))
do
    cd $j

    (time ./sad.exe ../../frame1.bmp ../../frame2.bmp) 2> time.txt

    cd ..
done

cd ..
