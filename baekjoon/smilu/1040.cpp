#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int count_set(int s) {
  int ret = 0;
  for (int i = 0; i < 10; i++) {
    ret += (s & (1 << i)) > 0;
  }
  return ret;
}

ll pw[19];
string s;
ll n, k;

ll mem[20][1<<10][2][2];
ll dp(int pos, int d_set, bool greater, bool starting) {
  ll &ret = mem[pos][d_set][greater][starting];
  if (ret != -1) return ret;

  if (pos == 19) {
    if (!greater) return ret = -2;
    if (count_set(d_set) != k) return ret = -2;
    return ret = 0;
  }

  ret = 0; 
  if (starting && s[pos] == 0) {
    ll t = dp(pos + 1, d_set, greater, starting);
    if (t >= 0) return ret = t;
  }
  int ib = greater ? 0 : s[pos];
  for (int i = ib; i < 10; i++) {
    if (starting && i == 0) continue;
    ll t = dp(pos + 1, d_set | (1 << i), greater || (i > s[pos]), starting && !i);
    if (t >= 0) return ret = t + pw[18-pos] * i;
  }
  return ret = -2;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < 19; i++) pw[i] = pw[i-1] * 10;
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> s >> k;

  int d_set = 0;
  for (char ch: s) d_set |= 1 << (ch - '0');
  if (count_set(d_set) == k) {
    cout << s << '\n';
    return 0;
  }

  while (s.size() < 19) s = '0' + s;
  for (char &ch: s) ch -= '0';
  memset(mem, 0xff, sizeof(mem));
  cout << dp(0, 0, 0, 1) << '\n';
}
