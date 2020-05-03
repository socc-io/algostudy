#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll t[100001], v[100001], n, D, ans;

ll cost(ll i, ll j) {
  return (j-i)*t[j]+v[i];
}

void dnq(ll s, ll e, ll l, ll r) {
  if (s > e) return;
  ll m = (s+e)>>1;
  ll k = max(l, m-D);
  for (ll i = k; i <= min(r, m); i++) {
    if (cost(k, m) < cost(i, m)) k = i;
  }
  ans = max(ans, cost(k, m));
  dnq(s, m-1, l, k);
  dnq(m+1, e, k, r);
}

int main(void)
{
  scanf("%lld%lld", &n, &D);
  for (int i = 1; i <= n; i++) scanf("%lld", &t[i]);
  for (int i = 1; i <= n; i++) scanf("%lld", &v[i]);
  dnq(1,n,1,n);
  printf("%lld\n", ans);
}
