#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 202020;
const int sq = 400;
const int sz = MAX_N/sq + 10;

struct Query {
  int x, y, i;
  void input(int i) {
    scanf("%d%d", &x, &y);
    --x;
    this->i = i;
  }
  bool operator<(const Query &q) const {
    if (x/sq != q.x/sq) return x < q.x;
    return y < q.y;
  }
} qs[MAX_N];

int n, q;
int arr[MAX_N];

list<int> pos[MAX_N];
int cnt[MAX_N], bucket[sz];
int ans[MAX_N];

void inc(const list<int> &dq) {
  if (dq.empty()) return;
  int v = dq.back() - dq.front();
  cnt[v]++;
  bucket[v/sq]++;
}

void dec(const list<int> &dq) {
  if (dq.empty()) return;
  int v = dq.back() - dq.front();
  cnt[v]--;
  bucket[v/sq]--;
}

void push(int x, bool d) {
  auto &dq = pos[arr[x]];
  dec(dq);
  d ? dq.push_back(x) : dq.push_front(x);
  inc(dq);
}

void pop(int x, bool d) {
  auto &dq = pos[arr[x]];
  dec(dq);
  d ? dq.pop_back() : dq.pop_front();
  inc(dq);
}

int query() {
  for (int i = sz-1; i >= 0; i--) {
    if (!bucket[i]) continue;
    for (int j = sq-1; j >= 0; j--) {
      if (cnt[i*sq+j] > 0) return i*sq+j;
    }
  }
  return 0;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
  for (int i = 1; i <= n; i++) arr[i] += arr[i-1];
  for (int i = 0; i <= n; i++) arr[i] += 100000;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) qs[i].input(i);
  sort(qs, qs+q);

  int l = qs[0].x, r = qs[0].y, x = qs[0].i;
  for (int i = l; i <= r; i++) push(i, true);
  ans[x] = query();

  for (int i = 1; i < q; i++) {
    x = qs[i].i;
		while(qs[i].x < l) push(--l, 0);
		while(r < qs[i].y) push(++r, 1);
		while(l < qs[i].x) pop(l++, 0);
		while(qs[i].y < r) pop(r--, 1);
		ans[x] = query();
  }

  for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
