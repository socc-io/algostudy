#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long lld;

vector<int> manacher_primitive(string s) {
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

vector<int> manacher(string s, char dummy = '.') {
  int n = s.size();
  string s2;
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

int main(void)
{
  string s;
  cin >> s;
  vector<int> res = manacher(s);
  lld ans = 0;
  for (int i = 0; i < res.size(); i++) {
    ans += (res[i] + 1) >> 1;
  }
  printf("%lld\n", ans);
}
