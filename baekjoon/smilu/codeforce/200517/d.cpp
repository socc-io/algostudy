#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000010;
const int MAX_SEG = MAX_N * 4;

struct Seg {
  int cnt[MAX_SEG];
  void update(int n, int s, int e, int x, int val) {
    if (x < s || x > e) return;
    if (s == e) {
      cnt[n] += val;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      update(l,s,m,x,val);
      update(r,m+1,e,x,val);
      cnt[n] = cnt[l] + cnt[r];
    }
  }
  void update(int x, int val) {
    update(1,1,MAX_N,x,val);
  }
  int query(int n, int s, int e, int left) {
    if (s == e) {
      if (left <= cnt[n]) return s;
      else return MAX_N;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (cnt[l] >= left) return query(l,s,m,left);
    left -= cnt[l];
    return query(r,m+1,e,left);
  }
  int query(int left) {
    return query(1,1,MAX_N,left);
  }
} seg;

int main(void)
{
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp);
    seg.update(tmp, 1);
  }
  for (int i = 0; i < q; i++) {
    int t; scanf("%d", &t);
    if (t < 0) {
      int v = seg.query(-t);
      seg.update(v, -1);
    } else {
      seg.update(t, 1);
    }
  }
  int v = seg.query(1);
  printf("%d\n", v % MAX_N);
}
