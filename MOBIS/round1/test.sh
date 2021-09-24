#!/bin/sh

g++ -o out $1.cpp --std=c++14
cat input.txt | ./out