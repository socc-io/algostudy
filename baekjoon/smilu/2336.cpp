#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF

struct student {
  int sc[3];
};

bool st_cmp(const student &a, const student &b) {
  return a.sc[0] < b.sc[0];
}

int n;
student st[500001];
int tree[2000004];

int update(int node, int start, int end, int index, int value) {
  if (index < start || end < index) return tree[node];
  if (start == end) return tree[node] = value;
  int mid = (start + end) >> 1;
  return tree[node] = min(
    update(node<<1, start, mid, index, value),
    update((node<<1)|1, mid+1, end, index, value)
  );
}

int get(int node, int start, int end, int left, int right) {
  if (right < start || end < left) return INF;
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) >> 1;
  return min(
    get(node<<1, start, mid, left, right),
    get((node<<1)|1, mid+1, end, left, right)
  );
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) { int t; scanf("%d", &t); st[t].sc[0] = i; }
  for (int i = 1; i <= n; i++) { int t; scanf("%d", &t); st[t].sc[1] = i; }
  for (int i = 1; i <= n; i++) { int t; scanf("%d", &t); st[t].sc[2] = i; }
  sort(st+1, st+n+1, st_cmp);
  for (int i = 1; i <= n; i++) update(1, 1, n, i, INF);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (get(1, 1, n, 1, st[i].sc[1]) > st[i].sc[2]) ++ans;
    update(1, 1, n, st[i].sc[1], st[i].sc[2]);
  }

  printf("%d\n", ans);
}
