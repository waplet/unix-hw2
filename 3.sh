#!/bin/bash

if [ -z "$1" ]; then
    echo "No search directory set";
    exit 1;
fi;

if [ -z "$2" ]; then
    echo "No destination directory set";
    exit 1;
fi;

DIR=$(pwd);
SEARCHDIR=$1;
DESTDIR=$2;

# Moving into search dir

# print total line
find $SEARCHDIR -type f |\
    xargs grep 'moveme' -c |\
    grep -Eo '[0-9]+$' |\
    awk '{ SUM += $1 } END { print SUM }';
# print moveable files 
find $SEARCHDIR -type f |\
    xargs grep -l 'moveme' |\
    wc -l

# movement
find $SEARCHDIR -type f |\
    xargs grep -l "moveme" |\
    xargs -I '{}' mv '{}' $DESTDIR
