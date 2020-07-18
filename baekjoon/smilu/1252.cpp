#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  string a, b; cin >> a >> b;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  const int sz = max(a.size(), b.size());
  string r(sz + 1, '0');
  int carry = 0;
  for (int i = 0; i < sz; i++) {
    const int p = i < a.size() ? a[i] - '0' : 0;
    const int q = i < b.size() ? b[i] - '0' : 0;
    const int v = p + q + carry;
    r[i] = '0' + (v & 1);
    carry = (v >> 1);
  }
  r[sz] = '0' + carry;

  bool flag = false;
  for (int i = sz; i >= 0; i--) {
    if (r[i] == '1') flag = true;
    if (!flag) continue;
    cout << r[i];
  }
  if (!flag) cout << '0';
}
