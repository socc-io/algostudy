#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

const int num_tiles = 2048 * 2048;
const char BLOCK_ICE = 'X';

int r, c, l1, l2;
vector<int> ttm(num_tiles);
queue<int> task;

struct UnionFind {
  vector<int> par;
  UnionFind(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
  }
  int root(int v) {
    return par[v] == v ? v : (par[v] = root(par[v]));
  }
  bool merge(int a, int b) {
    a = root(a);
    b = root(b);
    if (a == b) return false;
    par[b] = a;
    return true;
  }
  bool like(int a, int b) { return root(a) == root(b); }
} uf(num_tiles);

int index(int x, int y) {
    return (x << 11) | y;
}

bool inbound(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

void merge_around(int x, int y) {
    int i1 = index(x, y);
    if (ttm[i1] == -1) return;
    for (int i = 0; i < 4; i++) {
        int nx = x + dd[i][0], ny = y + dd[i][1];
        if (!inbound(nx, ny))
            continue;
        int i2 = index(nx, ny);
        if (ttm[i2] == -1) continue;
        uf.merge(i1, i2);
    }
}

void read() {
    char buf[2048];
    cin >> r >> c;
    l1 = -1;
    for (int x = 0; x < r; x++) {
        cin >> buf;
        for (int y = 0; y < c; y++) {
            ttm[index(x, y)] = (buf[y] == BLOCK_ICE ? -1 : 0);
            if (buf[y] == 'L') {
                if (l1 == -1) {
                    l1 = index(x, y);
                } else {
                    l2 = index(x, y);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    read();

    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            merge_around(x, y);
        }
    }

    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            int idx = index(x, y);
            if (ttm[idx] == 0) task.push(idx);
        }
    }

    while (!task.empty()) {
        int u = task.front();
        int x = u >> 11, y = u & 0x7ff;
        task.pop();
        for (int di = 0; di < 4; di++) {
            int nx = x + dd[di][0], ny = y + dd[di][1];
            if (!inbound(nx, ny)) continue;
            int v = index(nx, ny);
            if (ttm[v] != -1) continue;
            ttm[v] = ttm[u] + 1;
            task.push(v);
            merge_around(nx, ny);
            if (uf.like(l1, l2)) {
                cout << ttm[v];
                return 0;
            }
        }
    }
}
