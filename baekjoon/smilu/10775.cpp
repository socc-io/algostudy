#include <cstdio>

int g, p;
int par[100001];

int getpar(int x) { return x == par[x] ? x : (par[x] = getpar(par[x])); }

int main(void)
{
  int i;
  scanf("%d%d", &g, &p);
  for (i = 1; i <= g; i++) par[i] = i;
  for (i = 0; i < p; i++) {
    int t; scanf("%d", &t);
    int p = getpar(t);
    if (!p) break;
    par[p] = p-1;
  }
  printf("%d\n", i);
}
