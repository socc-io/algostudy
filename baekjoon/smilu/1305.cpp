#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi get_pi(string s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

vi kmp(string s, string q) {
  vi ans;
  vi pi = get_pi(q);
  int n = s.size(), m = q.size(), j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != q[j]) j = pi[j-1];
    if (s[i] == q[j]) {
      if (j == m-1) {
        ans.push_back(i-m+1);
        j = pi[j];
      } else {
        j++;
      }
    }
  }
  return ans;
}

int main() {
  int n; cin >> n;
  string s; cin >> s;
  auto pi = get_pi(s);
  cout <<  n-pi[n-1] << '\n';
}
