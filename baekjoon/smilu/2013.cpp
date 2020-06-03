#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
inline bool d_zero(double v) { return -eps < v && v < eps; }

bool distinct(double a, double b, double c, double d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return b < c || d < a;
}

struct point {
  double x, y;
  void input() { cin >> x >> y; }
  point operator-(const point &b) const {
    return point(x - b.x, y - b.y);
  }
  point(double x, double y): x(x), y(y) {}
  point() {}
};

double ccw(const point &a, const point &b) { return a.x*b.y - a.y*b.x; }
double ccw(const point &a, const point &b, const point &c) { return ccw(b-a, c-a); }

struct line {
  point a, b;
  void input() { a.input(); b.input(); }
  bool parallel(const line &l) const {
    if (!d_zero(ccw(a, b, l.a))) return false;
    if (!d_zero(ccw(a, b, l.b))) return false;
    if (distinct(a.x, b.x, l.a.x, l.b.x)) return false;
    if (distinct(a.y, b.y, l.a.y, l.b.y)) return false;
    return true;
  }
} lines[10000];

int n;
int par[10000];
int get_par(int x) { return x == par[x] ? x : (par[x] = get_par(par[x])); }
void init_par() { for (int i = 0; i < 10000; i++) par[i] = i; }
void merge(int a, int b) { par[get_par(b)] = get_par(a); }

bool check_conn(int a, int b) {
  return lines[a].parallel(lines[b]);
}

int main() {
  init_par();
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) lines[i].input();
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (check_conn(i, j)) merge(i, j);
    }
  }
  int cnt = 0; for (int i = 0; i < n; i++) cnt += (par[i] == i);
  cout << cnt << '\n';
}
