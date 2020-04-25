#include <bits/stdc++.h>
using namespace std;

int h, w;
bool marked[20][20];
int g[20][20][20][20];

int grundy(int x1, int y1, int x2, int y2) {
  if (x1 < 0 || x1 >= h) return 0;
  if (x2 < 0 || x2 >= h) return 0;
  if (y1 < 0 || y1 >= w) return 0;
  if (y2 < 0 || y2 >= w) return 0;

  int &ret = g[x1][y1][x2][y2];
  if (ret != -1) return ret;
  bool check[6] = {false, false, false, false, false, false};

  if (x1 > x2 || y1 > y2) return ret = 0;
  if (x1 == x2 && y1 == y2) return ret = !marked[x1][y1];

  for (int cx = x1; cx <= x2; cx++) {
    for (int cy = y1; cy <= y2; cy++) {
      if (marked[cx][cy]) continue;
      int gp = 0;
      int args[4][4] = {
        {x1,y1,cx-1,cy-1}, // lt
        {x1,cy+1,cx-1,y2}, // rt
        {cx+1,y1,x2,cy-1}, // lb
        {cx+1,cy+1,x2,y2}, // rb
      };
      for (int i = 0; i < 4; i++) {
        int prev = grundy(args[i][0], args[i][1], args[i][2], args[i][3]);
        gp ^= prev;
      }
      check[gp] = 1;
    }
  }
  ret = 0;
  while (check[ret]) ret++;
  return ret;
}

int main(void)
{
  memset(g, 0xFF, sizeof(g));
  char s[21];
  scanf("%d%d", &h, &w);
  for (int i = 0; i < h; i++) {
    scanf("%s", s);
    for (int j = 0; j < w; j++) {
      if (s[j] == 'X') marked[i][j] = true;
    }
  }
  puts(grundy(0, 0, h-1, w-1) > 0 ? "First" : "Second");
}
