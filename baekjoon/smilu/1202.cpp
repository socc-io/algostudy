#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Gem {
  int m, v;
  bool operator<(const Gem &g) const { return m < g.m; }
} gems[300000];
int n;

int bags[300000];
int k;

int main(void)
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d%d", &gems[i].m, &gems[i].v);
  for (int i = 0; i < k; i++) scanf("%d", &bags[i]);
  sort(gems, gems+n);
  sort(bags, bags+k);

  int g_piv = 0;
  ll v_sum = 0;
  priority_queue<int> q;
  for (int i = 0; i < k; i++) {
    while (g_piv < n && gems[g_piv].m <= bags[i]) {
      q.push(gems[g_piv].v);
      g_piv++;
    }
    if (!q.empty()) {
      v_sum += q.top(); q.pop();
    }
  }
  printf("%lld\n", v_sum);
}
