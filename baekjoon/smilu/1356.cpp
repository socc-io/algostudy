#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int mul(int a, int b) { return a*b; }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int v; cin >> v;
  vector<int> vs;
  while (v) {
    vs.push_back(v % 10);
    v /= 10;
  }
  for (int i = 1; i < vs.size(); i++) {
    if (accumulate(vs.begin(), vs.begin() + i, 1, mul) ==
        accumulate(vs.begin() + i, vs.end(), 1, mul)) {
      cout << "YES";
      return 0;
    }
  }
  cout << "NO";
}
