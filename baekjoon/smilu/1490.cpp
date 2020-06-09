#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);
  return b ? gcd(b, a%b) : a;
}

ll lcd(ll a, int b) { return (a / gcd(a, b)) * b; }

ll lcd(const vector<int> &vs) {
  ll ret = 1;
  for (int v: vs) if (v) ret = lcd(ret, v);
  return ret;
}

vector<int> decompose_digits(ll v) {
  vector<int> ret;
  while (v) {
    ret.push_back(v % 10);
    v /= 10;
  }
  return ret;
}

ll bfs(ll left, ll p) {
  queue<ll> q;
  q.push(left);
  while (1) {
    ll u = q.front(); q.pop();
    if (u % p == 0) return u;
    for (int i = 0; i <= 9; i++) q.push(u*10 + i);
  }
  return 0xdeadbeef;
}

ll solve(ll n) { return bfs(n, lcd(decompose_digits(n))); }
int main() { ll n; cin >> n; cout << solve(n); }
