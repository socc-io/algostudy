#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int,int> pii;

int n, m;
int sqrt_n;
int a[100000];
pii q[100000];
int q_ans[100000];
int cnt[100001];
int tbl[100001];
int ord[100000];
int ans;

bool sorter(int a, int b) {
  pii qa = q[a], qb = q[b];
  int sa = qa.first / sqrt_n, sb = qb.first / sqrt_n;
  if (sa != sb) return sa < sb;
  return qa.second < qb.second;
}

void add(int x) {
  if (cnt[x] != 0) tbl[cnt[x]]--;
  cnt[x]++;
  tbl[cnt[x]]++;
  ans = max(ans, cnt[x]);
}

void remove(int x) {
  tbl[cnt[x]]--;
  if (cnt[x] == ans && tbl[cnt[x]] == 0) --ans;
  cnt[x]--;
  tbl[cnt[x]]++;
}

void process_query(pii prev, pii curr) {
  int l1 = prev.first, r1 = prev.second;
  int l2 = curr.first, r2 = curr.second;
  for (int i = l2; i < l1; i++) add(a[i]);
  for (int i = l1; i < l2; i++) remove(a[i]);
  for (int i = r1; i < r2; i++) add(a[i]);
  for (int i = r2; i < r1; i++) remove(a[i]);
}

int main(void)
{
  scanf("%d", &n); sqrt_n = (int)sqrt(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  scanf("%d", &m);
  for (int i = 0; i < m; i++) scanf("%d%d", &q[i].first, &q[i].second);
  for (int i = 0; i < m; i++) ord[i] = i;
  sort(ord, ord + m, sorter);
  for (int i = 0; i < m; i++) q[i].first--;

  for (int i = q[ord[0]].first; i < q[ord[0]].second; i++) add(a[i]);
  q_ans[ord[0]] = ans;
  for (int i = 1; i < m; i++) {
    process_query(q[ord[i-1]], q[ord[i]]);
    q_ans[ord[i]] = ans;
  }
  for (int i = 0; i < m; i++) printf("%d\n", q_ans[i]);
}
