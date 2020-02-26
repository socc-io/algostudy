#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

vi get_sa(string str) {
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

int main(void)
{
  string s; cin >> s;
  vi sa = get_sa(s);
  for (int i = 0; i < sa.size(); i++) {
    printf("%d\n", sa[i]);
  }
}
