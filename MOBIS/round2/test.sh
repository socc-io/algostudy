#!/bin/sh
g++ -o out --std=c++14 $1.cc
cat input.txt | ./out