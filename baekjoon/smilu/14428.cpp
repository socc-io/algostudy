#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100010;
const int MAX_SEG = 4 * MAX_N;

struct Seg {
  int mv[MAX_SEG];
  int v[MAX_N] = {0x3f3f3f3f};
  int join(int l, int r) {
    if (v[l] <= v[r]) return l;
    return r;
  }
  void init(int n, int s, int e) {
    if (s == e) {
      mv[n] = s;
      cin >> v[s];
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      init(l,s,m); init(r,m+1,e);
      mv[n] = join(mv[l], mv[r]);
    }
  }
  void update(int n, int s, int e, int x, int nv) {
    if (s == e) {
      v[s] = nv;
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) update(l,s,m,x,nv);
    else update(r,m+1,e,x,nv);
    mv[n] = join(mv[l], mv[r]);
    // cout << "update " << s << ' ' << e << ": " << mv[n] << '\n';
  }
  int query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return mv[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    int L = query(l,s,m,f,t), R = query(r,m+1,e,f,t);
    return join(L, R);
  }
} seg;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  seg.init(1,1,n);
  int q; cin >> q;
  while (q--) {
    int a, b, c; cin >> a >> b >> c;
    if (a == 1) {
      seg.update(1,1,n,b,c);
    } else {
      cout << seg.query(1,1,n,b,c) << '\n';
    }
  }
}
