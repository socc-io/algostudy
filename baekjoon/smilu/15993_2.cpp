#include <cstdio>
#include <cstring>

#define MATSIZE 6
#define MOD 1000000009

typedef long long lld;

struct Matrix {
    lld v[MATSIZE][MATSIZE];
};
void matmul(Matrix* a, Matrix* b, Matrix* d)
{
    memset(d, 0, sizeof(Matrix));
    for (int i = 0; i < MATSIZE; i++) {
        for (int j = 0; j < MATSIZE; j++) {
            for (int k = 0; k < MATSIZE; k++) {
                d->v[i][j] += a->v[i][k] * b->v[k][j];
                d->v[i][j] %= MOD;
            }
        }
    }
}

/*

python3

import numpy as np
m = [np.mat([
    [0,0,1,0,0,0],
    [0,0,0,1,0,0],
    [0,0,0,0,1,0],
    [0,0,0,0,0,1],
    [0,1,0,1,0,1],
    [1,0,1,0,1,0],
], np.int64)]
for i in range(16):
  m.append((m[-1] * m[-1]) % 1000000009)

s = b''
for n in m:
  s += n.tobytes()

q = ''.join(['\\x'+hex(a)[2:] for a in s])
print('imp:', q)
print('one:', np.mat(np.eye(6), np.int64).tobytes())

*/

const char* imp = "\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x1\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x4\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x2\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x3\x0\x0\x0\x0\x0\x0\x0\x4\x0\x0\x0\x0\x0\x0\x0\x7\x0\x0\x0\x0\x0\x0\x0\x6\x0\x0\x0\x0\x0\x0\x0\xa\x0\x0\x0\x0\x0\x0\x0\xa\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\x6\x0\x0\x0\x0\x0\x0\x0\x7\x0\x0\x0\x0\x0\x0\x0\xa\x0\x0\x0\x0\x0\x0\x0\xa\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\x13\x0\x0\x0\x0\x0\x0\x0\x12\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\xc\x0\x0\x0\x0\x0\x0\x0\x12\x0\x0\x0\x0\x0\x0\x0\x13\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x22\x0\x0\x0\x0\x0\x0\x0\x22\x0\x0\x0\x0\x0\x0\x0\x29\x0\x0\x0\x0\x0\x0\x0\x28\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x16\x0\x0\x0\x0\x0\x0\x0\x22\x0\x0\x0\x0\x0\x0\x0\x22\x0\x0\x0\x0\x0\x0\x0\x28\x0\x0\x0\x0\x0\x0\x0\x29\x0\x0\x0\x0\x0\x0\x0\x55\x3\x0\x0\x0\x0\x0\x0\x54\x3\x0\x0\x0\x0\x0\x0\x24\x5\x0\x0\x0\x0\x0\x0\x24\x5\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x54\x3\x0\x0\x0\x0\x0\x0\x55\x3\x0\x0\x0\x0\x0\x0\x24\x5\x0\x0\x0\x0\x0\x0\x24\x5\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x75\x9\x0\x0\x0\x0\x0\x0\x74\x9\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x20\x6\x0\x0\x0\x0\x0\x0\x74\x9\x0\x0\x0\x0\x0\x0\x75\x9\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x64\x11\x0\x0\x0\x0\x0\x0\x64\x11\x0\x0\x0\x0\x0\x0\xb9\x14\x0\x0\x0\x0\x0\x0\xb8\x14\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x44\xb\x0\x0\x0\x0\x0\x0\x64\x11\x0\x0\x0\x0\x0\x0\x64\x11\x0\x0\x0\x0\x0\x0\xb8\x14\x0\x0\x0\x0\x0\x0\xb9\x14\x0\x0\x0\x0\x0\x0\xc9\x27\xdf\x0\x0\x0\x0\x0\xc8\x27\xdf\x0\x0\x0\x0\x0\x88\x7b\x58\x1\x0\x0\x0\x0\x88\x7b\x58\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\xc8\x27\xdf\x0\x0\x0\x0\x0\xc9\x27\xdf\x0\x0\x0\x0\x0\x88\x7b\x58\x1\x0\x0\x0\x0\x88\x7b\x58\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x29\x9a\x79\x2\x0\x0\x0\x0\x28\x9a\x79\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x60\x72\x9a\x1\x0\x0\x0\x0\x28\x9a\x79\x2\x0\x0\x0\x0\x29\x9a\x79\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\x48\x60\x8d\x4\x0\x0\x0\x0\x48\x60\x8d\x4\x0\x0\x0\x0\x11\x88\x6c\x5\x0\x0\x0\x0\x10\x88\x6c\x5\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\xe8\xed\xf2\x2\x0\x0\x0\x0\x48\x60\x8d\x4\x0\x0\x0\x0\x48\x60\x8d\x4\x0\x0\x0\x0\x10\x88\x6c\x5\x0\x0\x0\x0\x11\x88\x6c\x5\x0\x0\x0\x0\x8d\x44\xb4\x33\x0\x0\x0\x0\x8c\x44\xb4\x33\x0\x0\x0\x0\x1d\x44\x56\x25\x0\x0\x0\x0\x1d\x44\x56\x25\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\x8c\x44\xb4\x33\x0\x0\x0\x0\x8d\x44\xb4\x33\x0\x0\x0\x0\x1d\x44\x56\x25\x0\x0\x0\x0\x1d\x44\x56\x25\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\x74\x16\x61\x9\x0\x0\x0\x0\x73\x16\x61\x9\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\xf0\x9b\x47\x11\x0\x0\x0\x0\x73\x16\x61\x9\x0\x0\x0\x0\x74\x16\x61\x9\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xf4\xb1\x4a\xc\x0\x0\x0\x0\xf4\xb1\x4a\xc\x0\x0\x0\x0\x78\x2c\x64\x4\x0\x0\x0\x0\x77\x2c\x64\x4\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xd\xe0\x9d\x36\x0\x0\x0\x0\xf4\xb1\x4a\xc\x0\x0\x0\x0\xf4\xb1\x4a\xc\x0\x0\x0\x0\x77\x2c\x64\x4\x0\x0\x0\x0\x78\x2c\x64\x4\x0\x0\x0\x0\x86\xcb\x6b\x21\x0\x0\x0\x0\x85\xcb\x6b\x21\x0\x0\x0\x0\x96\x8e\x7f\x37\x0\x0\x0\x0\x96\x8e\x7f\x37\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\x85\xcb\x6b\x21\x0\x0\x0\x0\x86\xcb\x6b\x21\x0\x0\x0\x0\x96\x8e\x7f\x37\x0\x0\x0\x0\x96\x8e\x7f\x37\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\x5a\xb6\xa9\x1a\x0\x0\x0\x0\x59\xb6\xa9\x1a\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\xdd\xb4\xd8\x34\x0\x0\x0\x0\x59\xb6\xa9\x1a\x0\x0\x0\x0\x5a\xb6\xa9\x1a\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x3e\x64\xfb\x29\x0\x0\x0\x0\x3e\x64\xfb\x29\x0\x0\x0\x0\xbb\x65\xcc\xf\x0\x0\x0\x0\xba\x65\xcc\xf\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x6a\x79\xbd\x30\x0\x0\x0\x0\x3e\x64\xfb\x29\x0\x0\x0\x0\x3e\x64\xfb\x29\x0\x0\x0\x0\xba\x65\xcc\xf\x0\x0\x0\x0\xbb\x65\xcc\xf\x0\x0\x0\x0\xe7\x46\xca\x15\x0\x0\x0\x0\xe6\x46\xca\x15\x0\x0\x0\x0\x42\xf5\x5c\x6\x0\x0\x0\x0\x42\xf5\x5c\x6\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\xe6\x46\xca\x15\x0\x0\x0\x0\xe7\x46\xca\x15\x0\x0\x0\x0\x42\xf5\x5c\x6\x0\x0\x0\x0\x42\xf5\x5c\x6\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x16\x1a\x42\x2d\x0\x0\x0\x0\x15\x1a\x42\x2d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x2f\xd3\x77\x17\x0\x0\x0\x0\x15\x1a\x42\x2d\x0\x0\x0\x0\x16\x1a\x42\x2d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\xa0\x9b\x4c\x35\x0\x0\x0\x0\xa0\x9b\x4c\x35\x0\x0\x0\x0\x7e\x18\x7c\xf\x0\x0\x0\x0\x7d\x18\x7c\xf\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\x71\xc8\xd4\x1d\x0\x0\x0\x0\xa0\x9b\x4c\x35\x0\x0\x0\x0\xa0\x9b\x4c\x35\x0\x0\x0\x0\x7d\x18\x7c\xf\x0\x0\x0\x0\x7e\x18\x7c\xf\x0\x0\x0\x0\x44\xff\x71\x17\x0\x0\x0\x0\x43\xff\x71\x17\x0\x0\x0\x0\x2b\x63\xc5\x25\x0\x0\x0\x0\x2b\x63\xc5\x25\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\x43\xff\x71\x17\x0\x0\x0\x0\x44\xff\x71\x17\x0\x0\x0\x0\x2b\x63\xc5\x25\x0\x0\x0\x0\x2b\x63\xc5\x25\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\x33\x11\x6c\x36\x0\x0\x0\x0\x32\x11\x6c\x36\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\xef\x11\xfa\x1e\x0\x0\x0\x0\x32\x11\x6c\x36\x0\x0\x0\x0\x33\x11\x6c\x36\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x0\xbd\x1e\x28\x0\x0\x0\x0\x0\xbd\x1e\x28\x0\x0\x0\x0\x3b\xf2\xf5\x3\x0\x0\x0\x0\x3a\xf2\xf5\x3\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x11\xab\x24\x9\x0\x0\x0\x0\x0\xbd\x1e\x28\x0\x0\x0\x0\x0\xbd\x1e\x28\x0\x0\x0\x0\x3a\xf2\xf5\x3\x0\x0\x0\x0\x3b\xf2\xf5\x3\x0\x0\x0\x0\xba\x14\xe\x24\x0\x0\x0\x0\xb9\x14\xe\x24\x0\x0\x0\x0\x3f\x1a\x0\x26\x0\x0\x0\x0\x3f\x1a\x0\x26\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\xb9\x14\xe\x24\x0\x0\x0\x0\xba\x14\xe\x24\x0\x0\x0\x0\x3f\x1a\x0\x26\x0\x0\x0\x0\x3f\x1a\x0\x26\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\xea\x52\x94\x2b\x0\x0\x0\x0\xe9\x52\x94\x2b\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\x30\x3e\x86\x7\x0\x0\x0\x0\xe9\x52\x94\x2b\x0\x0\x0\x0\xea\x52\x94\x2b\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x9f\x96\xc\x35\x0\x0\x0\x0\x9f\x96\xc\x35\x0\x0\x0\x0\x50\xe1\x7f\x1d\x0\x0\x0\x0\x4f\xe1\x7f\x1d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x6f\x58\x86\x2d\x0\x0\x0\x0\x9f\x96\xc\x35\x0\x0\x0\x0\x9f\x96\xc\x35\x0\x0\x0\x0\x4f\xe1\x7f\x1d\x0\x0\x0\x0\x50\xe1\x7f\x1d\x0\x0\x0\x0\x6\x2b\xf1\x28\x0\x0\x0\x0\x5\x2b\xf1\x28\x0\x0\x0\x0\xc7\x8\x27\xb\x0\x0\x0\x0\xc7\x8\x27\xb\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\x5\x2b\xf1\x28\x0\x0\x0\x0\x6\x2b\xf1\x28\x0\x0\x0\x0\xc7\x8\x27\xb\x0\x0\x0\x0\xc7\x8\x27\xb\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd4\x6c\xcd\xe\x0\x0\x0\x0\xd3\x6c\xcd\xe\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd7\xb\x77\x21\x0\x0\x0\x0\xd3\x6c\xcd\xe\x0\x0\x0\x0\xd4\x6c\xcd\xe\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x6c\x56\x7a\x12\x0\x0\x0\x0\x6c\x56\x7a\x12\x0\x0\x0\x0\x72\x81\x6b\x3b\x0\x0\x0\x0\x71\x81\x6b\x3b\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x9e\x14\x9e\x2c\x0\x0\x0\x0\x6c\x56\x7a\x12\x0\x0\x0\x0\x6c\x56\x7a\x12\x0\x0\x0\x0\x71\x81\x6b\x3b\x0\x0\x0\x0\x72\x81\x6b\x3b\x0\x0\x0\x0\x5\xed\x6a\x1f\x0\x0\x0\x0\x4\xed\x6a\x1f\x0\x0\x0\x0\x9c\x5e\x71\x29\x0\x0\x0\x0\x9c\x5e\x71\x29\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\x4\xed\x6a\x1f\x0\x0\x0\x0\x5\xed\x6a\x1f\x0\x0\x0\x0\x9c\x5e\x71\x29\x0\x0\x0\x0\x9c\x5e\x71\x29\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa0\xbe\x1f\x14\x0\x0\x0\x0\x9f\xbe\x1f\x14\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\xa4\x9b\x4f\x30\x0\x0\x0\x0\x9f\xbe\x1f\x14\x0\x0\x0\x0\xa0\xbe\x1f\x14\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\xd2\x1\xdb\x12\x0\x0\x0\x0\xd2\x1\xdb\x12\x0\x0\x0\x0\xd7\xee\x45\x32\x0\x0\x0\x0\xd6\xee\x45\x32\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\x37\x30\x26\x1e\x0\x0\x0\x0\xd2\x1\xdb\x12\x0\x0\x0\x0\xd2\x1\xdb\x12\x0\x0\x0\x0\xd6\xee\x45\x32\x0\x0\x0\x0\xd7\xee\x45\x32\x0\x0\x0\x0\xdc\xad\xd1\x2d\x0\x0\x0\x0\xdb\xad\xd1\x2d\x0\x0\x0\x0\x4e\x41\xf9\x30\x0\x0\x0\x0\x4e\x41\xf9\x30\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\xdb\xad\xd1\x2d\x0\x0\x0\x0\xdc\xad\xd1\x2d\x0\x0\x0\x0\x4e\x41\xf9\x30\x0\x0\x0\x0\x4e\x41\xf9\x30\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\xf5\xb5\x1b\x11\x0\x0\x0\x0\xf4\xb5\x1b\x11\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\x22\xd2\xe4\x1e\x0\x0\x0\x0\xf4\xb5\x1b\x11\x0\x0\x0\x0\xf5\xb5\x1b\x11\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x89\x1b\x28\x33\x0\x0\x0\x0\x89\x1b\x28\x33\x0\x0\x0\x0\x5c\xff\x5e\x25\x0\x0\x0\x0\x5b\xff\x5e\x25\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x67\x49\x43\x14\x0\x0\x0\x0\x89\x1b\x28\x33\x0\x0\x0\x0\x89\x1b\x28\x33\x0\x0\x0\x0\x5b\xff\x5e\x25\x0\x0\x0\x0\x5c\xff\x5e\x25\x0\x0\x0\x0\x63\x95\x87\xc\x0\x0\x0\x0\x62\x95\x87\xc\x0\x0\x0\x0\x62\xb7\xc4\xb\x0\x0\x0\x0\x62\xb7\xc4\xb\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\x62\x95\x87\xc\x0\x0\x0\x0\x63\x95\x87\xc\x0\x0\x0\x0\x62\xb7\xc4\xb\x0\x0\x0\x0\x62\xb7\xc4\xb\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\x58\xbf\x6c\x1f\x0\x0\x0\x0\x57\xbf\x6c\x1f\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\xf5\x29\xe5\x12\x0\x0\x0\x0\x57\xbf\x6c\x1f\x0\x0\x0\x0\x58\xbf\x6c\x1f\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x4c\xb\x8f\x31\x0\x0\x0\x0\x4c\xb\x8f\x31\x0\x0\x0\x0\xa6\xd6\x7b\x2\x0\x0\x0\x0\xa5\xd6\x7b\x2\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x57\xe1\xa9\x1e\x0\x0\x0\x0\x4c\xb\x8f\x31\x0\x0\x0\x0\x4c\xb\x8f\x31\x0\x0\x0\x0\xa5\xd6\x7b\x2\x0\x0\x0\x0\xa6\xd6\x7b\x2\x0\x0\x0\x0\x56\x10\x25\x29\x0\x0\x0\x0\x55\x10\x25\x29\x0\x0\x0\x0\xc8\xf8\x32\x10\x0\x0\x0\x0\xc8\xf8\x32\x10\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x55\x10\x25\x29\x0\x0\x0\x0\x56\x10\x25\x29\x0\x0\x0\x0\xc8\xf8\x32\x10\x0\x0\x0\x0\xc8\xf8\x32\x10\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\xb0\x8c\xd1\x1c\x0\x0\x0\x0\xaf\x8c\xd1\x1c\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\x63\x46\x47\x2f\x0\x0\x0\x0\xaf\x8c\xd1\x1c\x0\x0\x0\x0\xb0\x8c\xd1\x1c\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x85\xbb\x26\x33\x0\x0\x0\x0\x85\xbb\x26\x33\x0\x0\x0\x0\xd2\x1\xb1\x20\x0\x0\x0\x0\xd1\x1\xb1\x20\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x22\x75\xdf\x3\x0\x0\x0\x0\x85\xbb\x26\x33\x0\x0\x0\x0\x85\xbb\x26\x33\x0\x0\x0\x0\xd1\x1\xb1\x20\x0\x0\x0\x0\xd2\x1\xb1\x20\x0\x0\x0\x0\xeb\xa3\x6a\xa\x0\x0\x0\x0\xea\xa3\x6a\xa\x0\x0\x0\x0\x38\x8\x8\x16\x0\x0\x0\x0\x38\x8\x8\x16\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\xea\xa3\x6a\xa\x0\x0\x0\x0\xeb\xa3\x6a\xa\x0\x0\x0\x0\x38\x8\x8\x16\x0\x0\x0\x0\x38\x8\x8\x16\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x76\xeb\xcb\x10\x0\x0\x0\x0\x75\xeb\xcb\x10\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x8b\x47\x61\x6\x0\x0\x0\x0\x75\xeb\xcb\x10\x0\x0\x0\x0\x76\xeb\xcb\x10\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\x4e\x97\xca\x22\x0\x0\x0\x0\x4e\x97\xca\x22\x0\x0\x0\x0\x39\x3b\x35\x2d\x0\x0\x0\x0\x38\x3b\x35\x2d\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\xc3\x4f\x69\x1c\x0\x0\x0\x0\x4e\x97\xca\x22\x0\x0\x0\x0\x4e\x97\xca\x22\x0\x0\x0\x0\x38\x3b\x35\x2d\x0\x0\x0\x0\x39\x3b\x35\x2d\x0\x0\x0\x0";
const char* one = "\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00";
Matrix *m = (Matrix*)imp;

int main(void)
{
    int T, N;
    Matrix n[2];
    int r[2];
    int f = 0;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &N);
        if (N == 1) {
            printf("0 1\n");
            continue;
        }
        --N;
        memcpy(n, one, sizeof(Matrix));
        for (int j = 0; N; j++, N >>= 1) {
            if (N & 1) {
                matmul(n + f, m + j, n + (1 - f));
                f = 1 - f;
            }
        }
        int* va = (int*)n[f].v;
        printf(
            "%lld %lld\n",
            ((long long)va[7] + va[8] + va[9] + 2 * (va[10] + va[11])) % MOD,
            ((long long)va[1] + va[2] + va[3] + 2 * (va[4] + va[5])) % MOD
        );
    }
}