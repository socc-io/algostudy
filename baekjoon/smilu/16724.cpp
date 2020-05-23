#include <bits/stdc++.h>
using namespace std;

int h, w, n;
char tile[1000][1001];
vector<int> adj[1000000];
int grp[1000000], g_piv = 1;
int offset[128];

void set_group(int u, int p) {
  grp[u] = g_piv;
  for (int v: adj[u]) {
    if (grp[v]) continue;
    set_group(v, u);
  }
}

int main(void)
{
  scanf("%d%d", &h, &w); n = h*w;
  offset[(int)'U'] = -w;
  offset[(int)'D'] =  w;
  offset[(int)'L'] = -1;
  offset[(int)'R'] =  1;
  for (int i = 0; i < h; i++) scanf("%s", tile[i]);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int u = i*w + j;
      int v = u + offset[(int)tile[i][j]];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
  for (int i = 0; i < n; i++) {
    if (grp[i]) continue;
    set_group(i, -1);
    g_piv++;
  }
  printf("%d\n", g_piv-1);
}
