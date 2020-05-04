#include <cstdio>
#include <algorithm>
using namespace std;

int solve(int n) {
  int n2 = n>>1;
  int s = (1<<(n+1)) - 2;
  int p2 = 0;
  for (int i = 0; i < n2; i++) {
    p2 |= 1<<(n-1-i);
  }
  return abs(s-p2*2);
}

int main(void)
{
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    printf("%d\n", solve(n));
  }
}
