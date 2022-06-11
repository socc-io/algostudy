#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
const int max_h = 9;

int n, m;
char tile[1<<6][1<<6];

//      x y h
// bits 6 6 4
int ext_x(int v) { return v >> 10; }
int ext_y(int v) { return (v >> 4) & 0x3f; }
int ext_h(int v) { return v & 0x0f; }
int compose(int x, int y, int h) { return (x << 10) | (y << 4) | h; }

bool unavailable(int x, int y, int h) {
    return x < 0 || x >= n || y < 0 || y >= m ||
        h < tile[x][y] || h > max_h;
}

bool unavailable(int v) {
    int x = ext_x(v), y = ext_y(v), h = ext_h(v);
    return unavailable(x, y, h);
}

vector<int> nexts(int origin) {
    vector<int> v(5);
    int ox = ext_x(origin), oy = ext_y(origin), oh = ext_h(origin);
    for (int di = 0; di < 4; di++)
        v[di] = compose(ox + dd[di][0], oy + dd[di][1], oh);
    v[4] = compose(ox, oy, oh + 1);
    return v;
}

vector<int> edges() {
    vector<int> v;
    v.reserve(1 << 16);
    for (int i = 0; i < n; i++) {
        v.push_back(compose(i, 0, tile[i][0])); // left
        if (m > 1)
            v.push_back(compose(i, m-1, tile[i][m-1])); // right
    }
    for (int i = 1; i < m-1; i++) {
        v.push_back(compose(0, i, tile[0][i])); // top
        if (n > 1)
            v.push_back(compose(n-1, i, tile[n-1][i])); // bottom
    }
    return v;
}

int main() {
    int count = 0;
    scanf("%d %d", &n, &m); 
    for (int i = 0; i < n; i++) {
        scanf("%s", tile[i]);
        for (int j = 0; j < m; j++)
            count += (tile[i][j] -= '0');
    }

    vector<bool> visit(1 << 16);
    vector<int> q = edges();
    for (int s: q) visit[s] = true;
    count += q.size();
    int f = 0, r = q.size();
    while (f < r) {
        for (int v: nexts(q[f++])) {
            if (unavailable(v) || visit[v])
                continue;
            visit[v] = true;
            q[r++] = v;
            count++;
        }
    }

    printf("%d", n*m*(max_h+1) - count);
}
