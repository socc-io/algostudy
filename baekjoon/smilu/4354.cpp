#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi get_pi(const string &s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

int solve(const string &s) {
  vi pi = get_pi(s);
  int n = s.length();
  // cout << "pi: "; for (int i = 0; i < n; i++) cout << pi[i] << ' '; cout << '\n';
  if (pi[n-1] % (n - pi[n-1])) return 1;
  return n / (n - pi[n-1]);
}

int main() {
  while (1) {
    string s;
    cin >> s;
    if (s == ".") break;
    cout << solve(s) << '\n';
  }
}