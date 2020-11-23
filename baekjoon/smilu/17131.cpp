#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200020

typedef long long ll;
const ll mod = 1000000007;

struct Point {
    ll x, y;
};

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
};

struct BIT {
  ll ft[MAX_N];
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
} lt_bit, rt_bit;

int n;
Point points[200000];
ll lt_cnt[200000], rt_cnt[200000];
int lt_indices[200000];
int rt_indices[200000];

bool cmp_lt(int a, int b) {
    if (points[a].y != points[b].y) {
        return points[a].y > points[b].y;
    }
    return points[a].x < points[b].x;
}

bool cmp_rt(int a, int b) {
    if (points[a].y != points[b].y) {
        return points[a].y > points[b].y;
    }
    return points[a].x > points[b].x;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
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
    iota(lt_indices, lt_indices + n, 0);
    sort(lt_indices, lt_indices + n, cmp_lt);
    iota(rt_indices, rt_indices + n, 0);
    sort(rt_indices, rt_indices + n, cmp_rt);

    int lt_check = 0, lt_y = points[lt_indices[0]].y;
    for (int i = 0; i < n; i++) {
        const int index = lt_indices[i];
        const Point p = points[index];
        if (p.y != lt_y) {
            for (int j = lt_check; j < i; j++) {
                lt_bit.update(points[lt_indices[j]].x, 1);
            }
            lt_check = i;
            lt_y = p.y;
        }
        lt_cnt[index] = lt_bit.query(1, p.x - 1);
    }

    int rt_check = 0, rt_y = points[rt_indices[0]].y;
    for (int i = 0; i < n; i++) {
        const int index = rt_indices[i];
        const Point p = points[index];
        if (p.y != rt_y) {
            for (int j = rt_check; j < i; j++) {
                rt_bit.update(points[rt_indices[j]].x, 1);
            }
            rt_check = i;
            rt_y = p.y;
        }
        rt_cnt[index] = rt_bit.query(p.x + 1, n + 2);
    }

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        ll num = lt_cnt[i] * rt_cnt[i];
        sum = (sum + num) % mod;
    }
    cout << sum << '\n';
}
