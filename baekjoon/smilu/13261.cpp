#include <cstdio>

typedef long long lld;

int l, g;
lld d[801][8001];
int p[801][8001];
lld s[8001];

inline lld c(int i, int j) {
  return (s[j] - s[i-1]) * (j-i+1);
}

void f(int t, int s, int e, int l, int r) {
  if (s > e) return;
  int m = (s + e) >> 1;
  d[t][m] = -1;
  p[t][m] = -1;
  for (int k = l; k <= r; k++) {
    lld tmp = d[t-1][k] + c(k+1, m);
    if (d[t][m] == -1 || d[t][m] > tmp) {
      d[t][m] = tmp;
      p[t][m] = k;
    }
  }
  f(t, s, m-1, l, p[t][m]);
  f(t, m+1, e, p[t][m], r);
}

int main(void)
{
  scanf("%d%d", &l, &g);
  for (int i = 0; i < l; i++) {
    lld tmp; scanf("%lld", &tmp);
    s[i+1] = s[i] + tmp;
  }
  for (int i = 0; i <= l; i++) {
    d[1][i] = c(1, i);
    p[1][i] = 0;
  }
  for (int i = 2; i <= g; i++) {
    f(i, 0, l, 0, l);
  }
  printf("%lld\n", d[g][l]);
}
