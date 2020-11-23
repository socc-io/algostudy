#include <bits/stdc++.h>
using namespace std;

#define MAX_N 80000

typedef long long ll;

struct BIT {
  ll ft[MAX_N];
  void clear() {
      memset(ft, 0x00, sizeof(ft));
  }
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  ll query(int a, int b) {
    return query(b) - query(a-1);
  }
};

class Zipper: public vector<int> {
public:
  void add(int v) { push_back(v); }
  void organize() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  int get(int v) {
    auto lo = lower_bound(begin(), end(), v);
    return distance(begin(), lo);
  }
};

struct Point {
    int x, y;
};

bool cmp_point(const Point &a, const Point &b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x > b.x;
}

int n;
Point points[75000];
BIT bit;

void solve() {
    cin >> n;
    Zipper x_zip, y_zip;
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        x_zip.add(points[i].x);
        y_zip.add(points[i].y);
    }
    x_zip.organize();
    y_zip.organize();
    for (int i = 0; i < n; i++) {
        points[i].x = x_zip.get(points[i].x) + 1;
        points[i].y = y_zip.get(points[i].y) + 1;
    }
    sort(points, points + n, cmp_point);
    bit.clear();
    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        const Point p = points[i];
        cnt += bit.query(p.x, n+10);
        bit.update(p.x, 1);
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
