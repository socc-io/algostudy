#include <cstdio>

#define INF 0x7FFFFFFF

const int dd[5][2] ={{0,0},{1,0},{-1,0},{0,1},{0,-1}};

inline int access(int i) { return (1 << i); }

struct Tile {
  int v[18];
  int n;
  int cnt;
  void invert(int x, int y) {
    v[x] ^= access(y);
  }
  bool outbound(int x, int y) {
    return x < 0 || x >= n || y < 0 || y >= n;
  }
  void press(int x, int y) {
    for (int di = 0; di < 5; di++) {
      int nx = x + dd[di][0], ny = y + dd[di][1];
      if (outbound(nx, ny)) continue;
      invert(nx, ny);
    }
    ++cnt;
  }
};

int get_line(int n) {
  int r = 0;
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp);
    r |= (access(i) * tmp);
  }
  return r;
}

int n;
Tile origin, sim;

int main(void)
{
  int ans = INF;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) origin.v[i] = get_line(n);
  origin.n = n;
  for (int fl = 0; fl < (1 << n); fl++) {
    sim = origin;
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        int ref = x == 0 ? fl : sim.v[x-1];
        if (ref & access(y)) sim.press(x, y);
      }
    }
    if (sim.v[n-1] == 0 && sim.cnt < ans) ans = sim.cnt; 
  }
  printf("%d\n", ans == INF ? -1 : ans);
}
