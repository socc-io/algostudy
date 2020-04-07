#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Query {
  int index, l, r, ans;
};

int n, m, uniq_num, local;
int a[1000000], b[1000000], c[1000000], qi[1000000];
Query q[1000000];

int mo_size;
bool mo_sort(const int r1, const int r2) {
  int t1 = q[r1].r / mo_size;
  int t2 = q[r2].r / mo_size;
  return t1 == t2 ? q[r1].l < q[r2].l : t1 < t2;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]); // get A
  for (int i = 0; i < n; i++) b[i] = a[i]; // copy B = A
  sort(b, b+n); // Unique B
  uniq_num = unique(b, b+n) - b;
  for (int i = 0; i < n; i++) a[i] = lower_bound(b, b+uniq_num, a[i]) - b; // Convert a[i] into own indices in B
  scanf("%d", &m); // Get queries
  for (int i = 0; i < m; i++) scanf("%d%d", &q[i].l, &q[i].r);
  for (int i = 0; i < m; i++) q[i].l--;
  for (int i = 0; i < m; i++) q[i].index = i;
  for (int i = 0; i < m; i++) qi[i] = i; // sort queries by mo's algorithm
  mo_size = sqrt(n);
  sort(qi, qi+m, mo_sort);
  int l = q[qi[0]].l, r = q[qi[0]].l ; // apply mo's algorithm
  for (int i = 0; i < m; i++) {
    int nl = q[qi[i]].l, nr = q[qi[i]].r;
    for (int j = l;   j <  nl; j++) local -= (--c[a[j]] == 0);
    for (int j = l-1; j >= nl; j--) local += (++c[a[j]] == 1);
    for (int j = r;   j <  nr; j++) local += (++c[a[j]] == 1);
    for (int j = r-1; j >= nr; j--) local -= (--c[a[j]] == 0);
    q[qi[i]].ans = local;
    l = nl; r = nr;
  }
  for (int i = 0; i < m; i++) printf("%d\n", q[i].ans);
}
