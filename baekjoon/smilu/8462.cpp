#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

struct Query {
  int index;
  int l, r;
  lld ans;
};
int mo_size;
bool mo_sort(const Query &a, const Query &b) {
  int p = a.r / mo_size;
  int q = b.r / mo_size;
  return p == q ? a.l < b.l : p < q;
}
bool index_sort(const Query &a, const Query &b) {
  return a.index < b.index;
}

int n;
int a[100000];
Query q[100000];

int cnt[1000001];
lld c;

void count(lld v) {
  c += v*(2*cnt[v]+1);
  ++cnt[v];
}

void discount(lld v) {
  c -= v*(2*cnt[v]-1);
  --cnt[v];
}

int main(void)
{
  int t;
  scanf("%d%d", &n, &t);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < t; i++) {
    int l, r; scanf("%d%d", &l, &r);
    q[i].l = --l;
    q[i].r = r;
    q[i].index = i;
  }
  mo_size = sqrt(t);
  sort(q, q+t, mo_sort);

  int l = 0, r = 0;
  for (int i = 0; i < t; i++) {
    int nl = q[i].l;
    int nr = q[i].r;
    for (int i = l; i < nl; i++) discount(a[i]);
    for (int i = l-1; i >= nl; i--) count(a[i]);
    for (int i = r; i < nr; i++) count(a[i]);
    for (int i = r-1; i >= nr; i--) discount(a[i]);
    q[i].ans = c;
    l = nl;
    r = nr;
  }
  sort(q, q+t, index_sort);
  for (int i = 0; i < t; i++) {
    printf("%lld\n", q[i].ans);
  }
}
