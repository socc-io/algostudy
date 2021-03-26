#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_SIZE = (1<<20);

inline int left(int x) { return ((x<<1)|1); }
inline int right(int x) { return left(x) + 1; }
inline int mid(int s, int e) { return ((s+e)>>1); }

class Zipper: public vector<ll> {
public:
  void add(ll v) { push_back(v); }
  void organize() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  ll get(ll v) {
    auto lo = lower_bound(begin(), end(), v);
    return distance(begin(), lo);
  }
} x_zip, y_zip;

struct Seg {
  ll cnt[MAX_SIZE];
  ll len[MAX_SIZE];
  void watch(int n, int s, int e) {
    if (!cnt[n]) {
      if (s == e) {
        len[n] = 0;
      } else {
        len[n] = len[left(n)] + len[right(n)];
      }
    }
  }
  void update(int n, int s, int e, int f, int t, int off) {
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      if (off > 0) {
        ++cnt[n];
        len[n] = y_zip[e+1] - y_zip[s];
      } else {
        --cnt[n];
        watch(n, s, e);
      }
    } else {
      int m = mid(s, e);
      update(left(n), s, m, f, t, off);
      update(right(n), m+1, e, f, t, off);
      watch(n, s, e);
    }
  }
} seg;

struct VerLine {
  ll x, y1, y2;
  int in;
};

bool cmp_ver_line(const VerLine &a, const VerLine &b) {
  if (a.x != b.x)   return a.x < b.x;
  if (a.y1 != b.y1) return a.y1 < b.y1;
  if (a.y2 != b.y2) return a.y2 < b.y2;
  return a.in < b.in;
}

int n;
VerLine ver_lines[400040];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x1, x2, y1, y2;
    cin >> x1 >> x2 >> y1 >> y2;
    ver_lines[(i<<1)] = {x1, y1, y2, 1};
    ver_lines[(i<<1)+1] = {x2, y1, y2, -1};
    x_zip.add(x1); x_zip.add(x2);
    y_zip.add(y1); y_zip.add(y2);
  }
  x_zip.organize();
  y_zip.organize();
  sort(ver_lines, ver_lines + (n<<1), cmp_ver_line);
  
  for (int i = 0; i < (n<<1); i++) {
    ver_lines[i].y1 = y_zip.get(ver_lines[i].y1);
    ver_lines[i].y2 = y_zip.get(ver_lines[i].y2);
  }

  ll ans = 0;
  ll x_cur = 0;
  for (int i = 0; i < (n<<1); i++) {
    VerLine line = ver_lines[i];
    ll nx = line.x;
    ll dx = nx - x_cur;
    ans += dx * seg.len[0];
    seg.update(0, 0, y_zip.size()-2, line.y1, line.y2 - 1, line.in);
    x_cur = nx;
  }
  cout << ans << '\n';
}
