#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;
typedef vector<lld> vi;

void print_vi(vi & v) {
  for (int i = 0; i < v.size(); i++) {
    printf("%lld ", v[i]);
  } puts("");
}

int main(void)
{
  int n, m, t;
  scanf("%d", &t);

  scanf("%d", &n);
  vi A = vi(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &A[i]);
  }
  scanf("%d", &m);
  vi B = vi(m);
  for (int i = 0; i < m; i++) {
    scanf("%lld", &B[i]);
  }

  // printf("A: "); print_vi(A);
  // printf("B: "); print_vi(B);

  vi As, Bs;
  As.reserve(n*n); Bs.reserve(n*n);

  for (int i = 0; i < n; i++) {
    lld sum = 0;
    for (int j = i + 1; j <= n; j++) {
      sum += A[j-1];
      As.push_back(sum);
    }
  }
  for (int i = 0; i < m; i++) {
    lld sum = 0;
    for (int j = i + 1; j <= m; j++) {
      sum += B[j-1];
      Bs.push_back(sum);
    }
  }

  sort(Bs.begin(), Bs.end());

  // printf("As: "); print_vi(As);
  // printf("Bs: "); print_vi(Bs);

  lld ans = 0;
  for (int i = 0; i < As.size(); i++) {
    lld a = As[i];
    auto lo = lower_bound(Bs.begin(), Bs.end(), t - a);
    auto up = upper_bound(Bs.begin(), Bs.end(), t - a);
    int cnt_b = up - lo;
    ans += cnt_b;
  }
  printf("%lld", ans);
}
