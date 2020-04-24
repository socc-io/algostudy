#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long lld;

int n, q;
lld arr[100001];

lld gcd(lld a, lld b) {
  if (a < b) swap(a, b);
  while (b) {
    lld t = a % b;
    a = b;
    b = t;
  }
  return a;
}

struct SumSeg {
  lld v[400000];
  lld lb[400000];
  lld build(int n, int s, int e) {
    if (s == e) return v[n] = arr[s];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return v[n] = build(l, s, m) + build(r, m+1, e);
  }
  void push(int n, int s, int e) {
    lld &b = lb[n];
    if (b == 0) return;
    v[n] += b*(e-s+1);
    if (s != e) {
      int l = n<<1, r = l+1;
      lb[l] += b;
      lb[r] += b;
    }
    b = 0;
  }
  lld update(int n, int s, int e, int f, int t, lld val) {
    push(n, s, e);
    if (t < s || e < f) return v[n];
    if (f <= s && e <= t) {
      lb[n] += val;
      push(n, s, e);
      return v[n];
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return v[n] = update(l, s, m, f, t, val) + update(r, m+1, e, f, t, val);
  }
  lld query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return query(l, s, m, f, t) + query(r, m+1, e, f, t);
  }
  void update(int f, int t, lld val) {
    update(1, 1, n, f, t, val);
  }
  lld query(int x) {
    return query(1, 1, n, x, x);
  }
} s_seg;

struct GcdSeg {
  lld v[400000];
  lld build(int n, int s, int e) {
    if (s == e) return v[n] = arr[s];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return v[n] = gcd(build(l, s, m), build(r, m+1, e));
  }
  lld update(int n, int s, int e, int f, int t, lld val) {
    if (t < s || e < f) return v[n];
    if (s == e) return v[n] = val;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return v[n] = gcd(update(l, s, m, f, t, val), update(r, m+1, e, f, t, val));
  }
  lld query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return gcd(query(l, s, m, f, t), query(r, m+1, e, f, t));
  }
  void update(int x, lld val) {
    update(1, 1, n, x, x, val);
  }
  lld query(int f, int t) {
    return query(1, 1, n, f, t);
  }
} g_seg;

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", &arr[i]);
  s_seg.build(1, 1, n);
  g_seg.build(1, 1, n);

  scanf("%d", &q);
  while (q--) {
    int t, a, b; scanf("%d%d%d", &t, &a, &b);
    if (t) {
      s_seg.update(a, b, t);
      lld now = s_seg.query(a-1) - s_seg.query(a);
      g_seg.update(a, abs(now));
      now = s_seg.query(b) - s_seg.query(b+1);
      g_seg.update(b+1, abs(now));
    } else {
      lld now = g_seg.query(a+1, b);
      now = gcd(now, s_seg.query(a));
      printf("%lld\n", now);
    }
  }
}

// 1.  Meat lover
// 2.  Veggie lover
// 3.  Pepperoni lover
// 4.  Supreme
// 5.  Chicken
// 6.  Super supreme
// 7.  Spicy Sicilian
// 8.  Hawaiian
// 9.  Triplinge meat Italiano
// 10. Italian trio
// 11. Cheese
// 12. Pepperoni
// 13. Italian sausage
// 14. Hawaiian
