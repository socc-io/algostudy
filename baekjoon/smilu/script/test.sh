#!/bin/sh
g++ --std=c++14 -o $1 $1.cpp
cat input.txt | ./$1