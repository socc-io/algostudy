#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class SumSeg {
  using T = ll;
  vector<T> _v;
  int _begin, _end, _size;
  T _update(int n, int s, int e, int x, T uv) {
    if (s == e) return _v[n] += uv;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) _update(l,s,m,x,uv);
    else        _update(r,m+1,e,x,uv);
    return _v[n] = _v[l] + _v[r];
  }
  T _query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return 0ll;
    if (f <= s && e <= t) return _v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return _query(l,s,m,f,t) + _query(r,m+1,e,f,t);
  }
public:
  SumSeg() {}
  SumSeg(int begin, int end) {
    _begin = begin;
    _end = end;
    _size = 1 << ((int)ceil(log2(end - begin + 1)) + 1);
    _v = vector<T>(_size);
  }
  T update(int x, T uv) {
    return _update(1, _begin, _end, x, uv);
  }
  T query(int f, int t) {
    return _query(1, _begin, _end, f, t);
  }
};

class SegSeg {
  vector<SumSeg> _v;
  int _begin, _end, _size;
  void _update(int n, int s, int e, int x, int y, ll uv) {
    _v[n].update(y, uv);
    if (s == e) return;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) _update(l,s,m,x,y,uv);
    else        _update(r,m+1,e,x,y,uv);
  }
  ll _query(int n, int s, int e, int xf, int xt, int yf, int yt) {
    if (xt < s || e < xf) return 0;
    if (xf <= s && e <= xt) return _v[n].query(yf, yt);
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return _query(l,s,m,xf,xt,yf,yt) + _query(r,m+1,e,xf,xt,yf,yt);
  }
public:
  SegSeg(int begin, int end) {
    _begin = begin;
    _end = end;
    _size = 1 << ((int)ceil(log2(end - begin + 1)) + 1);
    _v = vector<SumSeg>(_size);
    for (int i = 0; i < _size; i++) {
      _v[i] = SumSeg(begin, end);
    }
  }
  void update(int x, int y, ll uv) {
    return _update(1, _begin, _end, x, y, uv);
  }
  ll query(int xf, int xt, int yf, int yt) {
    return _query(1, _begin, _end, xf, xt, yf, yt);
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  SegSeg seg(0,n);
  vector<vector<ll>> tile(n+1, vector<ll>(n+1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int t; cin >> t;
      seg.update(i, j, t);
      tile[i][j] = t;
    }
  }
  while (m--) {
    int cd; cin >> cd;
    if (cd == 0) {
      int x, y, v; cin >> x >> y >> v;
      seg.update(x, y, v - tile[x][y]);
      tile[x][y] = v;
    } else if (cd == 1) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << seg.query(x1,x2,y1,y2) << '\n';
    }
  }
}
