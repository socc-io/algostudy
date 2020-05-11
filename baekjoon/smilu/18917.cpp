#include <cstdio>

typedef long long ll;

int main(void)
{
  ll sum = 0;
  int xs = 0;
  int m; scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int cmd; scanf("%d", &cmd);
    if (cmd == 1) {
      int x; scanf("%d", &x);
      sum += x;
      xs ^= x;
    } else if (cmd == 2) {
      int x; scanf("%d", &x);
      sum -= x;
      xs ^= x;
    } else if (cmd == 3) {
      printf("%lld\n", sum);
    } else {
      printf("%d\n", xs);
    }
  }  
}
