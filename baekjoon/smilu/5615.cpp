#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll seed = 1987152371;
ll mod = 1000000009;
ll salt = 113;

vector<ll> ans;

inline ll rnd() {  // 랜덤 함수이다.
  seed *= seed;
  seed %= mod;
  seed += salt;
  seed %= mod;
  return seed;
}

ll mult(ll x, ll y, ll m) {
  __int128 t = x;
  t *= y;
  t %= m;
  return (ll)t;
}

ll exp(ll x, ll y, ll m) {
  ll res = 1;
  while (y) {
    if (y & 1) res = mult(res, x, m);
    y >>= 1;
    x = mult(x, x, m);
  }
  return res;
}

ll gcd(ll a, ll b) {
  if (a < b) swap(a, b);
  while (b) {
    ll t = a % b;
    a = b;
    b = t;
  }
  return a;
}

bool withness(ll s, ll n) {
  ll t = n - 1;
  int cnt = 0;
  while ((t & 1) == 0) {
    ++cnt;
    t >>= 1;
  }
  ll x = exp(s, t, n);
  ll pre = x;
  for (int i = 0; i < cnt; i++) {
    x = mult(x, x, n);
    if (x == 1 && pre != 1 && pre != n-1) return true;
    pre = x;
  }
  return x != 1;
}

bool is_prime(ll n) {
  for (int i = 0; i < 10; i++) {
    ll tmp = rnd() % n;
    while (tmp == 0) tmp = rnd() % n;
    if (withness(tmp, n)) return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  int ret = 0;
  while (t--) {
    ll v; cin >> v;
    ret += is_prime((v<<1)|1);
  }
  cout << ret << '\n';
}
