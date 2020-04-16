#!/bin/sh
g++ $1.cpp -o $1 -O2 -Wall -lm -std=gnu++14
cat input.txt | time ./$1