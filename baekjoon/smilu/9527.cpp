#include <cstdio>
typedef long long ll;
ll relu(ll a) { return a&(~(a>>63)); }
ll count_bit(ll n) {
  ll ret = 0;
  ll mask = 1;
  for (ll k = 0; k < 54; k++) {
    ret += ((n&(~mask))>>1) + relu((n&mask) - (1ll<<k));
    mask = (mask<<1)|1;
  }
  return ret;
}

int main(void)
{
  ll a, b; scanf("%lld%lld", &a, &b);
  printf("%lld\n", count_bit(b+1) - count_bit(a));
}
