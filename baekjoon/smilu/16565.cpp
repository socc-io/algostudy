#include <cstdio>

const int mod = 10007;

int n;
int fac[60];

int pow(int a, int b) {
  int ret = 1;
  while (b) {
    if (b&1) {
      ret = (ret*a)%mod;
    }
    a = (a*a)%mod;
    b >>= 1;
  }
  return ret;
}

int inv(int a) { return pow(a, mod-2); }

int perm(int a, int b) {
  return (fac[a]*inv(fac[a-b]))%mod;
}
int comb(int a, int b) {
  return (perm(a, b)*inv(fac[b]))%mod;
}
int pow_m_1(int a) {
  return ((a&1)<<1)-1;
}
int f(int n, int k) {
  return (
    (
      comb(52 - 4*k, n - 4*k)
     *comb(13, k)
    ) % mod
  ) * pow_m_1(k);
}

int solve(int n) {
  int ans = 0;
  for (int k = 1; k <= n/4; k++) ans = (ans + f(n, k)) % mod;
  if (ans < 0) ans += mod;
  return ans;
}

int main() {
  fac[0] = 1;
  for (int i = 1; i < 60; i++) fac[i] = (fac[i-1]*i)%mod;
  int n; scanf("%d", &n);
  printf("%d\n", solve(n));
}
