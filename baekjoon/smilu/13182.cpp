#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const ll mod = 1000000007LL;

ll pow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) res = res*a%mod;
    a = a*a%mod;
    b >>= 1;
  }
  return res;
}

ll inv(ll v) {
  return pow(v, mod-2);
}

ll solve(ll r, ll g, ll b, ll k) {
  ll r1 = b;
  r1 *= inv(1+b); r1 %= mod;
  r1 = pow(r1, k);
  r1 = (1 - r1 + mod) % mod;
  r1 *= r; r1 %= mod;
  r1 += k; r1 %= mod;
  ll r2 = g*k%mod;
  r2 *= inv(b); r2 %= mod;
  return (r1+r2)%mod;
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) {
    ll a, b, c, d; scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
    printf("%lld\n", solve(a, b, c, d));
  }
}
