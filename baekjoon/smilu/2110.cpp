#include <bits/stdc++.h>
using namespace std;

int n, c;
int pos[200000];

bool test(int offset) {
  int cnt = 1;
  int cur = 0;
  while (cnt < c) {
    int nxt = lower_bound(pos, pos+n, pos[cur] + offset) - pos;
    if (nxt == n) return false;
    cur = nxt;
    ++cnt;
  }
  return true;
}

int main(void)
{
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; i++) scanf("%d", &pos[i]);
  sort(pos, pos + n);
  int l = 1;
  int r = pos[n-1] - pos[0];
  while (l < r) {
    // printf("%d, %d\n", l, r);
    int m = (l+r+1)>>1;
    if (test(m)) l = m;
    else r = m-1;
  }
  printf("%d\n", l);
}
