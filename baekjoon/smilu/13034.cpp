#include <cstdio>

int g[1001];
bool visit[1001];

// i - 2 - j >= j
// i - 2  >= 2 * je
int main(void)
{
  g[2] = 1;
  for (int i = 3; i < 1001; i++) {
    for (int j = 0; j < 1001; j++) visit[j] = false;
    int je = (i - 2) / 2;
    for (int j = 0; j <= je; j++) {
      int k = i - 2 - j;
      int v = g[j] ^ g[k];
      visit[v] = true;
    }
    int gi = 0;
    for (;gi < 1001; gi++) {
      if (visit[gi] == false) break;
    }
    g[i] = gi;
  }
  
  int n; scanf("%d", &n);
  printf("%d", g[n] > 0 ? 1 : 2);
}