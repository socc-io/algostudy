#include <cstdio>

struct Seg {
  int v;
  Seg *l, *r;
  Seg(int v, Seg *l, Seg *r): v(v),l(l),r(r) {}
  Seg* build(int x, int s, int e) {
    if (s <= x && x <= e) {
      if (s == e) return new Seg(v+1, 0, 0);
      int m = (s+e)>>1;
      return new Seg(v+1, l->build(x, s, m), r->build(x, m+1, e));
    }
    return this;
  }
  int query(int s, int e, int f, int t) {
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return v;
    int m = (s+e)>>1;
    return l->query(s, m, f, t) + r->query(m+1, e, f, t);
  }
};

int m;
Seg* rt[500001];
int rti;
const int qe = 0x7fffffff;

int xor_query(int x, int lev, int s, int e, Seg *l, Seg *r) {
  if (s == e) return s;
  int bit = (x & (1<<lev)) >> lev;
  bool right = false;
  if (bit) {
    if (l->l->v == r->l->v) right = true;
    else right = false;
  } else {
    if (l->r->v == r->r->v) right = false;
    else right = true;
  }
  int m = (s+e)>>1;
  if (right) return xor_query(x, lev-1, m+1, e, l->r, r->r);
  return xor_query(x, lev-1, s, m, l->l, r->l);
}

int nth_query(int begin, int end, Seg *l, Seg *r, int val) {
  if (begin == end) return begin;
  int len = r->l->v - l->l->v;
  int mid = (begin + end) >> 1;
  if (len >= val) return nth_query(begin, mid, l->l, r->l, val);
  return nth_query(mid+1, end, l->r, r->r, val - len);
}

int main(void)
{
  rt[0] = new Seg(0, 0, 0);
  rt[0]->l = rt[0]; rt[0]->r= rt[0];
  rti = 1;
  scanf("%d", &m);
  while (m--) {
    int c, l, r, x, k;
    scanf("%d", &c);
    if (c == 1) {
      scanf("%d", &x);
      rt[rti] = rt[rti-1]->build(x, 0, qe);
      rti++;
    } else if (c == 2) {
      scanf("%d%d%d", &l, &r, &x);
      printf("%d\n", xor_query(x, 30, 0, qe, rt[l-1], rt[r]));
    } else if (c == 3) {
      scanf("%d", &k);
      rti -= k;
    } else if (c == 4) {
      scanf("%d%d%d", &l, &r, &x);
      printf("%d\n", rt[r]->query(0, qe, 0, x) - rt[l-1]->query(0, qe, 0, x));
    } else if (c == 5) {
      scanf("%d%d%d", &l, &r, &k);
      printf("%d\n", nth_query(0, qe, rt[l-1], rt[r], k));
    }
  }
}
