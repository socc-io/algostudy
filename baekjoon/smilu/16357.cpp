#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAX_SEG = 1<<19;

struct MaxSeg {
  int lz[MAX_SEG];
  int mv[MAX_SEG];
  void push(int n, int s, int e) {
    if (lz[n] == 0) return;
    int l = n<<1, r = l|1;
    if (s != e) for(int v: {l, r}) lz[v] += lz[n];
    mv[n] += lz[n];
    lz[n] = 0;
  }
  void update(int n, int s, int e, int f, int t, int uv) {
    push(n, s, e);
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      lz[n] += uv;
      push(n, s, e);
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    update(l, s, m, f, t, uv);
    update(r, m+1, e, f, t, uv);
    mv[n] = max(mv[l], mv[r]);
  }
  int query(int n, int s, int e, int f, int t) {
    push(n, s, e);
    if (t < s || e < f) return 0;
    if (f <= s && e <= t) return mv[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    int L = query(l, s, m, f, t);
    int R = query(r, m+1, e, f, t);
    return max(L, R);
  }
  void update(int f, int t, int uv) {
    update(1, 1, 1<<18, f, t, uv);
  }
  int query(int f, int t) {
    return query(1, 1, 1<<18, f, t);
  }
} seg;

struct Zipper: public vector<int> {
  void organize() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  int get(int x) {
    return distance(begin(), lower_bound(begin(), end(), x)) + 1;
  }
};

inline bool including(int x, int y, int v) {
  return x <= v && v <= y;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  int n2 = n << 1;
  vector<pi> ranges(n);
  Zipper zip; zip.reserve(n2);
  for (auto &r: ranges) {
    int _t;
    cin >> _t >> r.second >> _t >> r.first;
    zip.push_back(r.first);
    zip.push_back(r.second);
  }
  zip.organize();
  for (auto &r: ranges) {
    r.first  = zip.get(r.first);
    r.second = zip.get(r.second);
  }
  sort(ranges.begin(), ranges.end());
  vector<pi> r_ranges(n);
  for (int i = 0; i < n; i++) r_ranges[i] = make_pair(ranges[i].second, ranges[i].first);
  sort(r_ranges.begin(), r_ranges.end());

  for (const auto &r: ranges) seg.update(r.first, r.second, 1);

  vector<int> v1(n2 + 1);
  for (int i = 1; i <= n2; i++) v1[i] = seg.query(i, i);

  int ret = 0;
  for (int l1 = 1; l1 <= n2; l1++) {
    auto lo = lower_bound(ranges.begin(), ranges.end(), make_pair(l1, 0));
    auto up = upper_bound(ranges.begin(), ranges.end(), make_pair(l1, 0x3f3f3f3f));
    for (auto it = lo; it != up; it++) {
      seg.update(it->first, it->second, -1);
    }

    lo = lower_bound(r_ranges.begin(), r_ranges.end(), make_pair(l1 - 1, 0));
    up = upper_bound(r_ranges.begin(), r_ranges.end(), make_pair(l1 - 1, 0x3f3f3f3f));
    for (auto it = lo; it != up; it++) {
      seg.update(it->second, it->first, 1);
    }

    ret = max(ret, v1[l1] + seg.query(1, n2));
  }

  cout << ret << '\n';
}
