#!/bin/bash

for (( i=0; i<=3; i++ ))
do
    if [ $i -eq 0 ]
    then
        cd "sad"
    else
        cd "sad$i"
    fi

    for (( j=1; j<=7; j++ ))
    do
        cd $j

        (time ./sad.exe ../../frame1.bmp ../../frame2.bmp) 2> time.txt

        cd ..
    done
    cd ..
done
