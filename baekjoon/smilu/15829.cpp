#include <cstdio>

#define MOD 1234567891
#define R 31

typedef long long lld;

int len;
char str[51];

int main(void)
{
  scanf("%d%s", &len, str);

  lld sum = 0;
  lld r = 1;
  for (int i = 0; i < len; i++) {
    int v = str[i] - 'a' + 1;
    sum = (sum + v * r) % MOD;
    r = (r * R) % MOD;
  }

  printf("%lld", sum);
}