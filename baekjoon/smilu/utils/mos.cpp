#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

struct Query {
  int index;
  int l, r;
  int ans;
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

int n, c, m;
int cs[300000];
Query ps[10000];
int cnt[10000];

void set_ans(Query& q) {
  int th = (q.r - q.l) / 2;
  for (int i = 0; i < 10000; i++) {
    if (cnt[i] > th) {
      q.ans = i;
      return;
    }
  }
  q.ans = -1;
  return;
}

int main(void)
{
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; i++) {
    scanf("%d", &cs[i]); --cs[i];
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &ps[i].l, &ps[i].r);
    ps[i].index = i;
    ps[i].l--;
  }
  mo_size = sqrt(n);
  sort(ps, ps + m, mo_sort);

  for (int i = ps[0].l; i < ps[0].r; i++) {
    cnt[cs[i]]++;
  }
  set_ans(ps[0]);
  
  int l = ps[0].l, r = ps[0].r;
  for (int i = 1; i < m; i++) {
    int nl = ps[i].l;
    int nr = ps[i].r;
    for (int i = l; i < nl; i++) cnt[cs[i]]--;
    for (int i = l-1; i >= nl; i--) cnt[cs[i]]++;
    for (int i = r; i < nr; i++) cnt[cs[i]]++;
    for (int i = r-1; i >= nr; i--) cnt[cs[i]]--;
    set_ans(ps[i]);
    l = nl;
    r = nr;
  }
  sort(ps, ps + m, index_sort);
  for (int i = 0; i < m; i++) {
    int ans = ps[i].ans;
    if (ans == -1) {
      puts("no");
    } else {
      printf("yes %d\n", ans + 1);
    }
  }
}
