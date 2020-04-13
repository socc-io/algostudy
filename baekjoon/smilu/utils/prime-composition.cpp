#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long lld;

long long seed = 1987152371;
long long mod = 1000000009;
long long salt = 113;

vector<lld> ans;

inline lld rnd() {  // 랜덤 함수이다.
  seed *= seed;
  seed %= mod;
  seed += salt;
  seed %= mod;
  return seed;
}

lld mult(lld x, lld y, lld m) {
  __int128 t = x;
  t *= y;
  t %= m;
  return (lld)t;
}

lld exp(lld x, lld y, lld m) {
  lld res = 1;
  while (y) {
    if (y & 1) res = mult(res, x, m);
    y >>= 1;
    x = mult(x, x, m);
  }
  return res;
}

lld gcd(lld a, lld b) {
  if (a < b) swap(a, b);
  while (b) {
    lld t = a % b;
    a = b;
    b = t;
  }
  return a;
}

bool withness(lld s, lld n) {
  lld t = n - 1;
  int cnt = 0;
  while ((t & 1) == 0) {
    ++cnt;
    t >>= 1;
  }
  lld x = exp(s, t, n);
  lld pre = x;
  for (int i = 0; i < cnt; i++) {
    x = mult(x, x, n);
    if (x == 1 && pre != 1 && pre != n-1) return true;
    pre = x;
  }
  return x != 1;
}

bool is_prime(lld n) {
  for (int i = 0; i < 10; i++) {
    lld tmp = rnd() % n;
    while (tmp == 0) tmp = rnd() % n;
    if (withness(tmp, n)) return false;
  }
  return true;
}

lld polard_rho(long long n) {
  if (is_prime(n)) return n;
  if (n == 1) return 1;
  if ((n & 1) == 0) return 2;
  lld x = rnd() % (n-1) + 2;
  lld y = x;
  lld c = rnd() % n + 1;
  lld d = 1;
  while (d == 1) {
    x = (mult(x,x,n)+c+n)%n;
    y = (mult(y,y,n)+c+n)%n;
    y = (mult(y,y,n)+c+n)%n;
    d = gcd(abs(x - y), n);
    if (d == n) return polard_rho(n);
  }
  if (is_prime(d)) return d;
  return polard_rho(d);
}

int main(void)
{
  long long a;
  scanf("%lld", &a);

  while (a > 1) {
    lld div = polard_rho(a);
    ans.push_back(div);
    a /= div;
  }
  sort(ans.begin(), ans.end());
  for (auto p: ans) {
    printf("%lld\n", p);
  }
}
