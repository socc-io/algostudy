#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000000;
const int MAX_SEG = 4 * MAX_N;

struct Seg {
  int cnt[MAX_SEG];
  void update(int n, int s, int e, int x, int off) {
    if (s == e) {
      cnt[n] += off;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      if (x <= m) update(l,s,m,x,off);
      else update(r,m+1,e,x,off);
      cnt[n] = cnt[l] + cnt[r];
    }
  }
  int query(int n, int s, int e, int dst) {
    if (s == e) {
      if (cnt[n]) return s;
      else return 0;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (cnt[l] < dst) return query(r,m+1,e,dst-cnt[l]);
    return query(l,s,m,dst);
  }
} seg;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int q; cin >> q;
  while (q--) {
    int a, b, c; cin >> a >> b;
    if (a == 1) {
      int ans = seg.query(1,1,MAX_N,b);
      if (ans) {
        cout << ans << '\n';
        seg.update(1,1,MAX_N,ans,-1);
      }
    } else {
      cin >> c;
      seg.update(1,1,MAX_N,b,c);
    }
  }
}
