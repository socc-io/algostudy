# -*- coding: utf8 -*-

# Randomly generate sample data, not including answer

import random, os, sys

if len(sys.argv) < 2: print 'please give me n'

num = int(sys.argv[1])
fname = 'input.txt' if len(sys.argv) < 3 else sys.argv[2]
buf = str(num) + '\n'
for i in range(num):
    x = random.randint(-10000, 10000)
    y = random.randint(-10000, 10000)
    buf += '{} {}\n'.format(x, y)

fp = open(fname, 'w')
fp.write(buf)
fp.close()
