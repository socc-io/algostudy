#include <bits/stdc++.h>
using namespace std;

int pw[10];
void init_pw() {
  pw[0] = 1;
  for (int i = 1; i < 10; i++) pw[i] = pw[i-1] * 10;
}

int len(int v) {
  int ret = 0;
  while (v) {
    v /= 10;
    ++ret;
  }
  return ret;
}

int swap_digits(int v, int m, const int i, const int j) {
  const int pi = pw[i];
  const int pj = pw[j];
  const int vi = v / pi % 10;
  const int vj = v / pj % 10;
  if (vi == 0 && j == m-1) throw -1;
  v -= vi * pi;
  v -= vj * pj;
  v += vj * pi;
  v += vi * pj;
  return v;
}

bool visit[1000001];

int main() {
  init_pw();
  ios::sync_with_stdio(0); cin.tie(0);
  int n, k; cin >> n >> k;
  const int m = len(n);
  int ans = -1;
  queue<pair<int,int>> q;
  q.push({n, k});
  visit[n] = true;
  while (!q.empty()) {
    const auto u = q.front(); q.pop();
    const int vs = u.second - 1;
    // cout << "pop: " << u.first << '\n';
    if (!u.second) { ans = max(ans, u.first); continue; }
    bool flag = false;
    bool flag2 = false;
    for (int i = 0; i < m; i++) {
      for (int j = i+1; j < m; j++) {
        try {
          const auto v = swap_digits(u.first, m, i, j);
          flag = true;
          if (v == u.first) flag2 = true;
          if (visit[v]) continue;
          visit[v] = true;
          q.push({v, vs});
        } catch(int err) { continue; }
      }
    }
    if (flag && (u.second & 1) == 0) ans = max(ans, u.first);
    else if (flag2) ans = max(ans, u.first);
  }
  cout << ans << '\n';
}
