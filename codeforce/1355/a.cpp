#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

int max_digit(ll value) {
  int ret = 0;
  while (value) {
    ret = max(ret, (int)(value % 10));
    value /= 10;
  }
  return ret;
}

int min_digit(ll value) {
  int ret = 10;
  while (value) {
    ret = min(ret, (int)(value % 10));
    value /= 10;
  }
  return ret % 10;
}

ll next(ll a) {
  return a + min_digit(a) * max_digit(a);
}

void solve() {
  ll a, k;
  scanf("%lld%lld", &a, &k);
  for (int i = 2; i <= k; i++) {
    ll na = next(a);
    if (na == a) break;
    a = na;
  }
  printf("%lld\n", a);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
