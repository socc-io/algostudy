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
} sieve(10000010);

bool is_prime(int x) { return sieve.get(x); }

deque<int> decompose(int x) {
  deque<int> res;
  while (x) {
    res.push_back(x % 10);
    x /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

int compose(const deque<int> &lst) {
  int res = 0;
  for (int i = 0; i < lst.size(); i++) {
    res = (res*10) + lst[i];
  }
  return res;
}

void rotate(deque<int> &lst) {
  int tmp = lst[0];
  lst.pop_front();
  lst.push_back(tmp);
}

bool solve(int x) {
  deque<int> lst = decompose(x);
  bool ans = false;
  for (int i = 0; i < lst.size() - 1; i++) {
    rotate(lst);
    if (lst[0] == 0) continue;
    int num = compose(lst);
    if (num != x && is_prime(num)) {
      ans = true;
      break;
    }
  }
  return ans;
}

int main() {
  int x; cin >> x;
  cout << (solve(x) ? "YES" : "NO") << '\n';
}