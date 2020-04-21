/**
 * http://noj.am/13546
 * Mo's algorithm, sqrt decomposition
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <list>
using namespace std;

const int sq = 300;
const int sz = 101010/sq + 10;

int n, k, m;
int arr[101010];
struct Query {
  int l, r, i;
  bool operator<(const Query &q) const {
    int a = r / sq, b = q.r / sq;
    return a == b ? l < q.l : a < b;
  }
} qs[101010];
int ans[101010];
list<int> deq[101010];
int cnt[101010];
int b_cnt[sz];

void count(int v) {
  cnt[v]++;
  b_cnt[v / sq]++;
}
void discount(int v) {
  cnt[v]--;
  b_cnt[v / sq]--;
}
void add(int index, bool dir) {
  int v = arr[index];
  list<int> &d = deq[v];
  if (d.size() > 0) discount(d.back() - d.front());
  if (dir) d.push_back(index);
  else d.push_front(index);
  count(d.back() - d.front());
}
void remove(int index, bool dir) {
  int v = arr[index];
  list<int> &d = deq[v];
  discount(d.back() - d.front());
  if (dir) d.pop_front();
  else d.pop_back();
  if (d.size() > 0) count(d.back() - d.front());
}
int query() {
  int p = sz-1;
  while (b_cnt[p] == 0 && p > 0) p--;
  int q = (p+1)*sq - 1;
  while (cnt[q] == 0 && q > 0) q--;
  return q;
}

int main(void)
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &qs[i].l, &qs[i].r);
    qs[i].l--; qs[i].r--;
    qs[i].i = i;
  }
  sort(qs, qs+m);

  int l = qs[0].l, r = qs[0].r;
  for (int i = qs[0].l; i <= qs[0].r; i++) add(i, true);
  ans[qs[0].i] = query();

  for (int i = 1; i < m; i++) {
    Query &q = qs[i];
    while (r < q.r) add(++r, true);
    while (l > q.l) add(--l, false);
    while (r > q.r) remove(r--, false);
    while (l < q.l) remove(l++, true);
    ans[q.i] = query();
  }
  for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
}
