#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;
const int dd[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int h, w;
int pos_crim[2];
char buf[128];
char jail[128][128];

int index(int x, int y) { return ((x << 7) | y); }
int ext_x(int index) { return ((index >> 7) & 0x7f); }
int ext_y(int index) { return index & 0x7f; }
bool outbound(int x, int y) { return x < 0 || x >= h || y < 0 || y >= w; }

void bfs2(vector<int> &dist, queue<int> &oq) {
    int u = oq.front();
    oq.pop();
    
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        int ux = ext_x(u), uy = ext_y(u), ud = dist[u];
        for (int di = 0; di < 4; di++) {
            int nx = ux + dd[di][0], ny = uy + dd[di][1], v = index(nx, ny);
            if (outbound(nx, ny)) continue;
            if (dist[v] != inf) continue;
            if (jail[nx][ny] == '*') continue;
            if (jail[nx][ny] == '#') {
                dist[v] = ud + 1;
                oq.push(v);
            } else {
                dist[v] = ud;
                q.push(v);
            }
        }
    }
}

vector<int> bfs(int src) {
    vector<int> dist(1 << 14, inf);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        bfs2(dist, q);
    }
    return dist;
}

vector<int> add_vector3(const vector<int> &v1, const vector<int> &v2, const vector<int> &v3) {
    vector<int> r(v1.size());
    for (int i = 0; i < r.size(); i++) {
        if (v1[i] == inf || v2[i] == inf || v3[i] == inf)
            r[i] = inf;
        else
            r[i] = v1[i] + v2[i] + v3[i];
    }
    return r;
}

void print_vec(const vector<int> &v) {
  for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        int t = v[index(i, j)];
        printf("%2d ", t == inf ? -1 : t);
      }
      puts("");
  }
  puts("");
}

void solve() {
  cin >> h >> w;
  h += 2;
  w += 2;

  int i_crim = 0;
  memset(jail, '.', sizeof(jail));
  for (int i = 1; i < h-1; i++) {
      cin >> buf;
      memcpy(jail[i] + 1, buf, w-2);
      for (int j = 1; j < w-1; j++) {
          if (jail[i][j] == '$') {
              pos_crim[i_crim++] = index(i, j);
          }
      }
  }

  vector<int> d1 = bfs(pos_crim[0]);
  vector<int> d2 = bfs(pos_crim[1]);
  vector<int> d3 = bfs(0);
  vector<int> d = add_vector3(d1, d2, d3);

//   for (int i = 0; i < h; i++) jail[i][w] = 0;
//   for (int i = 0; i < h; i++) puts(jail[i]);
//   puts("");

//   print_vec(d1);
//   print_vec(d2);
//   print_vec(d3);
//   print_vec(d);

  for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
          if (jail[i][j] == '#') {
              d[index(i, j)] -= 2;
          }
      }
  }

  int min_d = inf;
  for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
          min_d = min(min_d, d[index(i, j)]);
      }
  }

  printf("%d\n", min_d);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
