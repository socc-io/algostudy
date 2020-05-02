#!/usr/bin/env python3
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

xs = []
ys = []

data = open('./graph', 'r').read()
for line in data.split('\n'):
  if len(line) == 0: continue
  x, y, = line.split(' ')
  x = float(x)
  y = float(y)
  xs.append(x)
  ys.append(y)

plt.plot(xs, ys)
plt.show()
