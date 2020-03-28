#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFFFFFFFFFF

typedef long long lld;

lld d, p, q;

lld gcm(lld a, lld b) { // a > b
  while (b) {
    lld t = a % b;
    a = b;
    b = t;
  }
  return a;
}

inline lld ceil_fit(lld c, lld b) {
  return (c+b-1) / b * b;
}

int main(void)
{
  scanf("%lld%lld%lld", &d, &p, &q);
  if (p > q) swap(p, q); // assert p > q
  lld g = gcm(q, p);
  lld k = g*(p/g-1)*(q/g-1);
  if (k <= d) {
    printf("%lld\n", ceil_fit(d, g));
    return 0;
  }
  lld mv = INF, e = min((lld)sqrt(d) * q, ceil_fit(d, q));
  for (lld i = 0; i <= e; i += q) {
    lld v = ceil_fit(d - i, p) + i;
    mv = min(mv, v);
  }
  printf("%lld\n", mv);
}
