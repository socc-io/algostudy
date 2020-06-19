#include <bits/stdc++.h>
using namespace std;

vector<int> manacher_primitive(const vector<int> &s) {
  int n = s.size();
  vector<int> a(n);
  int r = 0, p = 0;
  for (int i = 0; i < n; i++) {
    a[i] = i <= r ? min(a[2*p-i], r-i) : 0;
    while (i-a[i]-1 >= 0 && i+a[i]+1 < n && s[i-a[i]-1] == s[i+a[i]+1]) ++a[i];
    if (r < i+a[i]) {
      r = i + a[i];
      p = i;
    }
  }
  return a;
}

vector<int> manacher(const vector<int> &s, int dummy = -1234) {
  int n = s.size();
  vector<int> s2;
  s2.resize(n*2+1);
  s2[0] = dummy;
  int idx = 1;
  for (int i = 0; i < n; i++) {
    s2[idx++] = s[i];
    s2[idx++] = dummy;
  }
  // cout << s2 << endl; // debug
  return manacher_primitive(s2);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<int> s(n);
  for (int &v: s) cin >> v;
  const auto man = manacher(s);
  int m; cin >> m;
  while (m--) {
    int a, b; cin >> a >> b;
    a = (a<<1) - 1;
    b = (b<<1) - 1;
    const int m = (a+b) >> 1;
    if (man[m] >= b-m+1) cout << "1\n";
    else cout << "0\n";
  }
}
