#include <cstdio>

#define INF 0x7FFFFFFF

const int dd[5][2] ={{0,0},{1,0},{-1,0},{0,1},{0,-1}};

inline int access(int i) { return (1 << (9 - i)); }

struct Tile {
  int v[11];
  int cnt;
  void invert(int x, int y) {
    v[x] ^= access(y);
  }
  bool outbound(int x, int y) {
    return x < 0 || x >= 11 || y < 0 || y >= 10;
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

int get_line() {
  char s[11];
  scanf("%s", s);
  int r = 0;
  for (int i = 0; i < 10; i++) {
    r |= (access(i) * (s[i] == 'O'));
  }
  return r;
}

Tile origin;
Tile sim;

int main(void)
{
  int ans = INF;
  for (int i = 1; i < 11; i++) origin.v[i] = get_line();
  for (int fl = 0; fl < (1 << 10); fl++) {
    sim = origin;
    sim.v[0] = fl;
    for (int x = 1; x < 11; x++) {
      for (int y = 0; y < 10; y++) {
        if (sim.v[x-1] & access(y)) sim.press(x, y);
      }
    }
    if (sim.v[10] == 0 && sim.cnt < ans) ans = sim.cnt; 
  }
  printf("%d\n", ans == INF ? -1 : ans);
}
