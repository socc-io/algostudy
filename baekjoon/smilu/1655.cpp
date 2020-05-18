#include <bits/stdc++.h>

struct Seg {
  int cnt[80000];
  void update(int n, int s, int e, int x, int v = 1) {
    if (x < s || x > e) return;
    if (s == e) {
      cnt[n] += v;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      update(l,s,m,x,v);
      update(r,m+1,e,x,v);
      cnt[n] = cnt[l] + cnt[r];
    }
  }
  int query(int n, int s, int e, int left) {
    if (s == e) return s;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (cnt[l] < left) return query(r,m+1,e,left-cnt[l]);
    return query(l,s,m,left);
  }
} seg;

int main(void)
{
  int n; scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int tmp; scanf("%d", &tmp);
    seg.update(1,-10000,10000,tmp);
    int m = i/2 + (i&1);
    printf("%d\n", seg.query(1,-10000,10000,m));
  }
}
