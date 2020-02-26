#include <cstdio>
#include <algorithm>
using namespace std;

int n, n2;
int arrs[4][4000];
int ps[16000000];

int main(void)
{
  scanf("%d", &n); n2 = n * n;
  for (int i = 0 ; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      scanf("%d", &arrs[j][i]);
    }
  }
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ps[k++] = arrs[2][i] + arrs[3][j];
    }
  }
  sort(ps, ps + n2);
  
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int l = arrs[0][i] + arrs[1][j];
      int* rl = lower_bound(ps, ps + n2, -l);
      int* ru = upper_bound(ps, ps + n2, -l);
      ans += ru - rl;
    }
  }
  printf("%lld", ans);
}