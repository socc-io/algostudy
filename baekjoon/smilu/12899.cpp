#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Seg {
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
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return _v[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return _query(l,s,m,f,t) + _query(r,m+1,e,f,t);
  }
public:
  Seg(int begin, int end) {
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

struct CountSeg: public Seg<int> {
  int _at(int n, int s, int e, int x) {
    if (s == e) return s;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (_v[l] < x) return _at(r,m+1,e,x-_v[l]);
    return _at(l,s,m,x);
  }
public:
  CountSeg(int max_value): Seg<int>(0,max_value) {}
  int insert(int x) {
    return update(x, 1);
  }
  int remove(int x) {
    return update(x, -1);
  }
  int at(int x) {
    if (x > _v[1]) return -0x3f3f3f3f;
    return _at(1,_begin,_end,x);
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  CountSeg cs(2000000);
  while (n--) {
    int cd, va; cin >> cd >> va;
    if (cd == 1) cs.insert(va);
    else if (cd == 2) {
      int ret = cs.at(va);
      cout << ret << '\n';
      cs.remove(ret);
    }
  }
}
