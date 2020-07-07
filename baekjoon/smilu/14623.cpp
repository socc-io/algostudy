#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll get() {
  ll ret = 0;
  char ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    ret = (ret<<1) | (ch&1);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll v = get() * get();
  string s;
  while (v) {
    s.push_back('0' + (v&1));
    v >>= 1;
  }
  reverse(s.begin(), s.end());
  cout << s;
}
