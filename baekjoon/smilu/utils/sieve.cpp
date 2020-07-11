#include <bits/stdc++.h>
using namespace std;

class Sieve {
  int max_n;
  vector<bool> chk;
  void solve() {
    chk[0] = true;
    chk[1] = true;
    for (int i = 2; i*i <= max_n; i++) {
      if (chk[i]) continue;
      for (int j = i*i; j <= max_n; j += i) {
        chk[j] = true;
      }
    }
  }
public:
  Sieve(int max_n): max_n(max_n), chk(max_n+1) { solve(); }
  bool get(int n) { return !chk[n]; }
};
