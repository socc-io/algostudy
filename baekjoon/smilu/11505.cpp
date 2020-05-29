#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 1000010;
const ll mod = 1000000007;

struct Seg {
  ll v[4*MAX_N];
  void init(int n, int s, int e) {
    if (s == e) {
      cin >> v[n];
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      init(l,s,m);
      init(r,m+1,e);
      v[n] = (v[l]*v[r])%mod;
    }
  }
  void update(int n, int s, int e, int x, ll va) {
    if (s == e) {
      v[n] = va;
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      if (x <= m) update(l,s,m,x,va);
      else update(r,m+1,e,x,va);
      v[n] = (v[l]*v[r])%mod;
    }
  }
  ll query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 1;
    if (f <= s && e <= t) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return (query(l,s,m,f,t)*query(r,m+1,e,f,t))%mod;
  }
} seg;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m, k; cin >> n >> m >> k;
  int q = m+k;
  seg.init(1,1,n);
  for (int i = 0; i < q; i++) {
    int a, b, c; cin >> a >> b >> c;
    if (a == 1) {
      seg.update(1,1,n,b,c);
    } else {
      cout << seg.query(1,1,n,b,c) << '\n';
    }
  }
}
