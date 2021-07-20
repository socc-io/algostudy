#!/bin/sh
g++ $1.cpp -o $1 -g -O2 -Wall -lm -std=gnu++14 -I .
cat input.txt | ./$1