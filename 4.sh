#!/bin/bash

MAXCOUNT=10
count=0

# number [1, 100]
number=$(($RANDOM % 100 + 1))

read guess

while [ $count -ne $MAXCOUNT ]; do
    count=$(($count + 1))
    
    if [ $number -eq $guess ]; then
        echo "Victory"
        exit 1;
    else
        echo "Tries left: $(($MAXCOUNT - $count))";
        if [ $guess -lt $number ]; then
            echo "Smaller";
        else
            echo "Greater";
        fi;
    fi;
    read guess
done
