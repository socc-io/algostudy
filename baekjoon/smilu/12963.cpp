#include <cstdio>
#include <algorithm>
using namespace std;

#define MOD 1000000007
typedef long long lld;

int n, m;
int xs[2000];
int ys[2000];
lld p3[2000];
lld ans;
int par[2000];
int getpar(int u) { return par[u] == u ? u : (par[u] = getpar(par[u])); }
void merge(int a, int b, int i) {
  a = getpar(a); b = getpar(b);
  if (a > b) swap(a, b);
  if (a == b) return;
  if (a == 0 && b == n-1) ans += p3[i];
  else if (a == 0) par[b] = a;
  else par[a] = b;
}
int like(int a, int b) { return getpar(a) == getpar(b); }

int main(void)
{
  scanf("%d%d", &n, &m);
  p3[0] = 1;
  for (int i = 1; i < 2000; i++) p3[i] = (p3[i-1]*3)%MOD;
  for (int i = 0; i < m; i++) scanf("%d%d", &xs[i], &ys[i]);
  for (int i = 0; i < 2000; i++) par[i] = i;
  for (int i = m-1; i >= 0; i--) merge(xs[i], ys[i], i);
  printf("%lld\n", ans % MOD);
}
