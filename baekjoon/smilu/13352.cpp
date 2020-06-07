#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

int ccw(pl a, pl b, pl c) {
  ll op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

bool in_line(pl p, pl a, pl b) {
  return ccw(a, b, p) == 0;
}

bool is_line(const vector<pl> &ps) {
  if (ps.size() < 2) return 1;
  auto piv0 = ps[0];
  auto piv1 = ps[1];
  for (auto p: ps) {
    if (!in_line(p, piv0, piv1)) return false;
  }
  return true;
}

bool try_piv(pl piv0, pl piv1, const vector<pl> &ps) {
  vector<pl> other;
  for (auto p: ps) {
    if (in_line(p, piv0, piv1)) continue;
    other.push_back(p);
  }
  return is_line(other);
}

int rnd(int n) {
  int ret = rand();
  if (ret < 0) ret *= -1;
  return ret % n;
}

bool solve(const vector<pl> &ps) {
  if (ps.size() <= 4) return true;
  const int epoch = 10;
  for (int ei = 0; ei < epoch; ei++) {
    int i = rnd(ps.size());
    int j = i;
    while (i == j) j = rnd(ps.size());
    if (try_piv(ps[i], ps[j], ps)) return true;
  }
  return false;
}

int main() {
  srand(time(0));
  int n; cin >> n;
  vector<pl> ps(n);
  for (int i = 0; i < n; i++) {
    cin >> ps[i].first >> ps[i].second;
  }
  cout << (solve(ps) ? "success" : "failure") << '\n';
}
