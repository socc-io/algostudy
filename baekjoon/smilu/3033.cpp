#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

vi get_sa(string str) {
  /*
  Get suffix array from string
  */
  int n = str.size(), t = 1;
  vi sa(n), g(n+1), tg(n+1);
  g[n] = tg[n] = -1;
  for (int i = 0; i < n; i++) {
    sa[i] = i;
    g[i] = str[i];
  }
  auto cmp = [&](int a, int b) {
    if (g[a] != g[b]) return g[a] < g[b];
    return g[a+t] < g[b+t];
  };
  while (t < n) {
    sort(sa.begin(), sa.end(), cmp);
    tg[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      tg[sa[i]] = tg[sa[i-1]] + (cmp(sa[i-1],sa[i]) ? 1 : 0);
    }
    g = tg;
    t <<= 1;
  }
  return sa;
}

vi get_lcp(string str, vi sa) {
  /*
  Get longest common prefix array
  */
  int n = sa.size(), len = 0;
  vi r(n), lcp(n);
  for (int i = 0; i < n; i++) r[sa[i]] = i;
  for (int i = 0; i < n; i++) {
    int k = r[i];
    if (k) {
      int j = sa[k-1];
      while (str[j+len] == str[i+len]) ++len;
      lcp[k] = len;
      if (len) -- len;
    }
  }
  return lcp;
}

int main(void)
{
  int n; string s;
  cin >> n >> s;
  vi sa = get_sa(s);
  vi lcp = get_lcp(s, sa);
  int ans = 0;
  for (int i = 0; i < lcp.size(); i++) {
    if (lcp[i] > ans) ans = lcp[i];
  }
  printf("%d", ans);
}