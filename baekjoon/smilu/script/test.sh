#!/bin/sh
g++ $1.cpp -o $1 -g -O2 -Wall -lm -std=c++14 -I .
cat input.txt | time ./$1