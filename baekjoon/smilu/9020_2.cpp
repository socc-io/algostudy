#include <cstdio>

int not_prime[10100];

void sieve() {
  not_prime[0] = 1;
  not_prime[1] = 1;
  for (int i = 2; i < 10100; i++) {
    if (not_prime[i]) continue;
    for (int j = (i * 2); j < 10100; j += i) {
      not_prime[j] = 1;
    }
  }
}

void solve(int n) {
  int h = n / 2; // half of n
  for (int i = 0; i < h; i++) {
    int l = h - i;
    int r = h + i;

    // Both number must be prime
    if (not_prime[l] || not_prime[r]) continue;

    printf("%d %d\n", l, r);

    break;
  }
}

int main() {
  sieve();

  int t; scanf("%d", &t);

  while (t--) {
    int n; scanf("%d", &n);
    solve(n);
  }
}
