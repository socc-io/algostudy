#include <bits/stdc++.h>
using namespace std;

struct Vec2i {
    int x;
    int y;
    bool operator < (const Vec2i &o) {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

const int i_inf = 0x3f3f3f3f;
const int dd[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int n;
int board[20][20];

int sx, sy;
int sz = 2;
int csz = 2; // increment sz when csz becomes 0 
int g_time = 0;

Vec2i find_starting() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 9) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool outbound(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= n;
}

void eat(int x, int y, int distance) {
    // move
    sx = x;
    sy = y;

    // increase size
    --csz;
    if (csz <= 0) {
        csz = ++sz;
    }

    // past time
    g_time += distance;

    // remove fish
    board[x][y] = 0;
}

bool step() {
    queue<Vec2i> q;
    vector<int> distance(1 << 10, i_inf);

    q.push({sx, sy});
    distance[(sx << 5) | sy] = 0;

    vector<Vec2i> candidates;
    int d_candidates = i_inf;

    while (!q.empty()) {
        Vec2i u = q.front();
        int ui = (u.x << 5) | u.y;
        q.pop();

        if (distance[ui] > d_candidates) break;
        
        if (board[u.x][u.y] > 0 && board[u.x][u.y] < sz) {
            d_candidates = distance[ui];
            candidates.push_back(u);
        }

        for (int di = 0; di < 4; di++) {
            int nx = u.x + dd[di][0];
            int ny = u.y + dd[di][1];
            int ni = (nx << 5) | ny;
            if (outbound(nx, ny) || board[nx][ny] > sz || distance[ni] < i_inf) {
                continue;
            }
            distance[ni] = distance[ui] + 1;
            q.push({nx, ny});
        }
    }
    
    if (candidates.empty()) {
        return false;
    }

    sort(candidates.begin(), candidates.end());

    Vec2i t = candidates[0];
    eat(t.x, t.y, d_candidates);
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    Vec2i sv = find_starting();
    sx = sv.x;
    sy = sv.y;
    board[sx][sy] = 0;

    while (step());

    printf("%d", g_time);
}
