#include <bits/stdc++.h>
using namespace std;

const int mod = 360000;

typedef vector<int> vi;

vi get_pi(const vi &s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

bool kmp(const vi &s, const vi &q) {
  vi pi = get_pi(q);
  int n = s.size(), m = q.size(), j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != q[j]) j = pi[j-1];
    if (s[i] == q[j]) {
      if (j == m-1) {
        return true;
        j = pi[j];
      } else {
        j++;
      }
    }
  }
  return false;
}

vi diffs(const vi &vs) {
  int n = (int)vs.size();
  vi ret(n);
  for (int i = 0; i < n-1; i++) {
    ret[i] = vs[i+1] - vs[i];
  }
  ret[n-1] = vs[0] + mod - vs[n-1];
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vi a(n), b(n);
  for (int &v: a) cin >> v;
  for (int &v: b) cin >> v;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  vi c = diffs(a), d = diffs(b);
  vi c2(n*2);
  copy(c.begin(), c.end(), c2.begin());
  copy(c.begin(), c.end(), c2.begin() + n);
  cout << (kmp(c2, d) ? "possible\n" : "impossible\n");
}
