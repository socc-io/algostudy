#include <bits/stdc++.h>
using namespace std;

const int MAX_SEG = 1<<18;

struct ToggleSeg {
  int tc[MAX_SEG];
  bool tl[MAX_SEG];
  void push(int n, int s, int e) {
    if (tl[n] == false) return;
    const int l = n << 1, r = l | 1;
    if (s != e) for (int v: {l, r}) tl[v] = !tl[v];
    tc[n] = (e-s+1) - tc[n];
    tl[n] = false;
  }
  void toggle(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      tl[n] = !tl[n];
      push(n, s, e);
      return;
    }
    int m = (s+e)>>1, l = n << 1, r = l|1;
    toggle(l, s, m, f, t);
    toggle(r, m+1, e, f, t);
    tc[n] = tc[l] + tc[r];
  }
  int query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return tc[n];
    int m = (s+e)>>1, l = n << 1, r = l|1;
    int L = query(l, s, m, f, t);
    int R = query(r, m+1, e, f, t);
    return L + R;
  }
  void toggle(int f, int t) {
    toggle(1, 1, (1<<17), f, t);
  }
  int query(int f, int t) {
    return query(1, 1, (1<<17), f, t);
  }
} seg;

// void print_status(const int n) {
//   cout << "stat: ";
//   for (int i = 1; i <= n; i++)
//     cout << seg.query(i, i) << ' ';
//   cout << '\n';
// }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  while (m--) {
    int c, a, b; cin >> c >> a >> b;
    if (c == 0) {
      seg.toggle(a, b);
      // print_status(n);
    } else {
      // cout << '(' << a << ", " << b << "): ";
      cout << seg.query(a, b) << '\n';
    }
  }
}
