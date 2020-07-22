#include <bits/stdc++.h>
using namespace std;

const int inf = 0x4f4f4f4f;

typedef pair<int,int> pi;

int n;
int ls[200020];
int rs[200020];
int rt[200020][19];

set<pi> s;
pi vs[200020];
vector<pi> seq;

bool cmp(pi a, pi b) {
  if (a.second != b.second) return a.second < b.second;
  return a.first > b.first;
}

int sub(int s, int e) {
  if (s > e) return 0;
  int ps = lower_bound(seq.begin(), seq.end(), pi(s, -1))->second;
  int ret = 1;
  if (ps == n || vs[ps].second > e) return 0;
  for (int i = 18; i >= 0; i--) {
    if (rt[ps][i] == n) continue;
    if (vs[rt[ps][i]].second > e) continue;
    ret += (1 << i);
    ps = rt[ps][i];
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ls[i] >> rs[i];
    vs[i] = pi(ls[i], rs[i]);
  }
  sort(vs, vs + n, cmp);
  for (int i = 0; i < n; i++) {
    if (!seq.empty() && seq.back().first >= vs[i].first) continue;
    seq.push_back(pi(vs[i].first, i));
  }
  seq.push_back(pi(inf, n));
  int cur = 0;
  for (int i = 0; i < n; i++) {
    while (cur < n && vs[i].second >= vs[cur].first) ++cur;
    rt[i][0] = cur;
  }
  rt[n][0] = n;
  for (int i = 1; i < 19; i++) {
    rt[n][i] = n;
    for (int j = n-1; j >= 0; j--) {
      rt[j][i] = rt[rt[j][i-1]][i-1];
    }
  }
  s.insert(pi(-1, inf));
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    auto it = s.upper_bound(pi(ls[i], inf));
    --it;
    if (it->second < rs[i]) continue;
    const int target = sub(it->first, it->second);
    const int result = sub(it->first, ls[i] - 1) + sub(rs[i] + 1, it->second) + 1;
    if (target != result) continue;
    if (it->first <= ls[i] - 1) s.insert(pi(it->first, ls[i] - 1));
    if (rs[i] + 1 <= it->second) s.insert(pi(rs[i] + 1, it->second));
    s.erase(it);
    ans.push_back(i);
  }
  cout << ans.size() << '\n';
  for (int v: ans) cout << (v + 1) << ' '; cout << '\n';
}
