#include <bits/stdc++.h>
using namespace std;

const int MAX_SEG = 1<<20;

struct XorSeg {
  int val[MAX_SEG];
  int lz[MAX_SEG];
  void push(int n, int s, int e) {
    if (lz[n] == 0) return;
    int l = n << 1, r = l|1;
    if (s != e) for (int v: {l, r}) lz[v] ^= lz[n];
    else val[n] ^= lz[n];
    lz[n] = 0;
  }
  void update(int n, int s, int e, int f, int t, int uv) {
    push(n, s, e);
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      lz[n] ^= uv;
      push(n, s, e);
      return;
    }
    int m = (s+e)>>1, l = n << 1, r = l|1;
    update(l, s, m, f, t, uv);
    update(r, m+1, e, f, t, uv);
    val[n] = val[l] ^ val[r];
  }
  int query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return val[n];
    int m = (s+e)>>1, l = n << 1, r = l|1;
    int L = query(l, s, m, f, t);
    int R = query(r, m+1, e, f, t);
    return L ^ R;
  }
  void update(int f, int t, int uv) {
    update(1, 0, (1<<19)-1, f, t, uv);
  }
  int query(int f, int t) {
    return query(1, 0, (1<<19)-1, f, t);
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
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int v; cin >> v; seg.update(i, i, v);
  }
  // print_status(n);
  int m; cin >> m;
  while (m--) {
    int cmd, i, j, k; cin >> cmd >> i >> j;
    if (cmd == 1) {
      cin >> k;
      seg.update(i, j, k);
      // print_status(n);
    } else {
      // cout << "(" << i << ", " << j << "): ";
      cout << seg.query(i, j) << '\n';
    }
  }
}
