#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct item {
  ll x, y;
  bool operator<(const item &i) const { return x < i.x; }
} bs[250000];

int main(void)
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld%lld", &bs[i].x, &bs[i].y);
  for (int i = 0; i < n; i++) bs[i].x += bs[i].y;
  sort(bs, bs+n);
  priority_queue<ll> q;
  ll h = 0;
  for (int i = 0; i < n; i++) {
    h += bs[i].y;
    q.push(bs[i].y);
    while (h > bs[i].x) {
      h -= q.top(); q.pop();
    }
  }
  printf("%lu\n", q.size());
}
