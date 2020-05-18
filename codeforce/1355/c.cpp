#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

int main(void) {
  ll A, B, C, D; scanf("%lld%lld%lld%lld", &A, &B, &C, &D);
  ll S_begin = A + B;
  ll S_end = B + C + 1;
  ll ret = 0;
  for (ll s = S_begin; s < S_end; s++) {
    ll x_begin = max(A, s-C), x_end = min(B, s-B) + 1;
    ll num = x_end - x_begin;
    ll z_end = min(s-1, D) + 1;
    ll z_num = max(0ll, z_end - C);
    ret += num * z_num;
  }
  printf("%lld\n", ret);
}
