#include <bits/stdc++.h>
using namespace std;

const int max_n = 100001;
const int inf = 0x3f3f3f3f;

vector<int> next(int v) {
  vector<int> ret;
  if (v-1    >= 0  ) ret.push_back(v-1);
  if (v+1    <  max_n) ret.push_back(v+1);
  if ((v<<1) <  max_n) ret.push_back(v<<1);
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> dist(max_n, inf);
  vector<int> trk(max_n);
  iota(trk.begin(), trk.end(), 0);
  dist[n] = 0;
  queue<int> q;
  q.push(n);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: next(u)) {
      if (dist[v] != inf) continue;
      dist[v] = dist[u] + 1;
      trk[v] = u;
      q.push(v);
    }
  }
  vector<int> ans;
  int cur = k;
  while (trk[cur] != cur) {
    ans.push_back(cur);
    cur = trk[cur];
  }
  ans.push_back(cur);
  reverse(ans.begin(), ans.end());
  cout << ans.size()-1 << '\n';
  for (int v: ans) cout << v << ' '; cout << '\n';
}
