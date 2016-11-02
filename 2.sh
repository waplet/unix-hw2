#!/bin/bash

A=$(cat a)
B=$(cat b)
C=$(($A*$B))

touch c
echo $C > c
