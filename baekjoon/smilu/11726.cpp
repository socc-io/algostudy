#include <cstdio>

#define MOD 10007

int rs[1001];

void inspect(int n) {
  rs[n] = (rs[n - 2] + rs[n - 1]) % MOD;
}

int main(void)
{
  int n;
  scanf("%d", &n);

  rs[0] = 0;
  rs[1] = 1;
  rs[2] = 2;

  for (int i = 3; i <= n; i++) inspect(i);

  printf("%d", rs[n]);
}