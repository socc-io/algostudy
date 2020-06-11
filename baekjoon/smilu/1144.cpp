#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

int n, m;
int cost[100];

struct state {
  int index;
  int v[9];
  bool operator<(const state &s) const {
    if (index != s.index) return index < s.index;
    for (int i = 0; i < m; i++)
      if (v[i] != s.v[i]) return v[i] < s.v[i];
    return false;
  }
  bool should_set() const {
    if (back() == 0) return false;
    for (int i = 0; i < m-1; i++) {
      if (v[i] == back()) return false;
    }
    return true;
  }
  bool consistent() const {
    int cv = -1;
    for (int i = 0; i < m; i++) if (v[i]) {
      if (cv == -1) cv = v[i];
      else if (v[i] != cv) return false;
    }
    return true;
  }
  int max_v() const {
    int ret = v[0];
    for (int i = 1; i < m; i++) ret = max(ret, v[i]);
    return ret;
  }
  state merge_back_front() const {
    state ret(index + 1);
    for (int i = 0; i < m-1; i++) {
      ret.v[i+1] = v[i] == back() ? front() : v[i];
    }
    ret.v[0] = front();
    ret.normalize();
    return ret;
  }
  void normalize() {
    int chk[10]; memset(chk, 0x00, sizeof(chk));
    int piv = 1;
    for (int i = 0; i < m; i++) if (v[i]) {
      if (chk[v[i]] == 0) chk[v[i]] = piv++;
      v[i] = chk[v[i]];
    }
  }
  state shl(int blk) const {
    state ret(index + 1);
    memcpy(ret.v + 1, v, sizeof(int)*(m-1));
    ret.v[0] = blk;
    ret.normalize();
    return ret;
  }
  int back()  const { return v[m-1]; }
  int front() const { return index % m == 0 ? 0 : v[0]; }
  state(int index): index(index) {}
  state() {}
};

map<state, int> mem;

int dp(const state &s) {
  auto it = mem.find(s);
  if (it != mem.end()) return it->second;

  if (s.index >= n*m) {
    int ret = s.consistent() ? 0 : inf;
    mem.insert({s, ret});
    return ret;
  }

  int ret = s.consistent() ? 0 : inf;

  if (!s.should_set()) {
    ret = min(ret, dp(s.shl(0)));
  }

  const state nxt = s.front()
    ? (
      s.back()
        ? s.merge_back_front()
        : s.shl(s.front())
    )
    : (
      s.back()
        ? s.shl(s.back())
        : s.shl(s.max_v()+1)
    );
  ret = min(ret, dp(nxt) + cost[s.index]);

  mem.insert({s, ret});
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n*m; i++) cin >> cost[i];
  state init(0); memset(&init, 0x00, sizeof(state));
  cout << dp(init) << '\n';
}
