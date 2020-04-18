#!/bin/sh
g++ 2927.cpp -o 2927 -O2 -Wall -lm -std=gnu++14
cat otoci/otoci.in.1 | ./2927 > out
diff -q out otoci/otoci.out.1