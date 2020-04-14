#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

int cnt[100001];

vi get_pi(const string &s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

vi get_ls(const vi &pi) {
  vi ls;
  int cur = pi.size();
  while (cur > 0) {
    ls.push_back(cur);
    cur = pi[cur - 1];
  }
  reverse(ls.begin(), ls.end());
  return ls;
}

int main(void)
{
  string s; cin >> s;
  int n = s.size();
  vi pi = get_pi(s), ls = get_ls(pi);

  for (int i = n; i >= 1; i--) {
    ++cnt[i];
    cnt[pi[i-1]] += cnt[i];
  }

  cout << ls.size() << '\n';
  for (int i = 0; i < ls.size(); i++) {
    cout << ls[i] << ' ' << cnt[ls[i]] << '\n';
  }
}
