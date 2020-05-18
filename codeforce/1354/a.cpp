#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll a, ll b, ll c, ll d) {
  ll t = b;
  if (t >= a) return t;
  ll left = a - b;

  ll point = c - d;
  if (point <= 0) return -1;
  ll cnt = (left + point - 1) / point;

  t += c * cnt;
  
  return t;
}

void solve() {
  ll a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
  printf("%lld\n", solve(a, b, c, d));
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();  
}
