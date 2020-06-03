#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

ll pow(ll a, ll b, ll mod) {
  ll ret = 1;
  while (b) {
    if (b & 1) ret = (ret * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return ret;
}

pl chinese(const vector<pl> &conds) {
  const int n = conds.size();
  ll m = 1;
  for (const auto &cond: conds) m *= cond.first;
  vector<ll> ns(n);
  for (int i = 0; i < n; i++) ns[i] = m / conds[i].first;
  vector<ll> ss(n);
  for (int i = 0; i < n; i++) {
    const ll mod = conds[i].first;
    const ll tmp = ns[i] % mod;
    ss[i] = pow(tmp, mod - 2, mod);
  }
  ll ret = 0;
  for (int i = 0; i < n; i++) {
    ll tmp = (conds[i].second * ns[i]) % m;
    tmp = (tmp * ss[i]) % m;
    ret = (ret + tmp) % m;
  }
  return make_pair(m, ret);
}

vector<ll> decompose(ll v) {
  vector<ll> ret;
  for (ll i = 2; v > 1; i++) {
    if (v % i == 0) {
      ret.push_back(i);
      while (v % i == 0) v /= i;
    }
  }
  return ret;
}

pl general_chinese(const vector<pl> &conds) {
  vector<pl> strict_conds;
  for (const auto &cond: conds) {
    vector<ll> fs = decompose(cond.first);
    for (const auto &f: fs) {
      strict_conds.emplace_back(f, cond.second % f);
    }
  }
  return chinese(strict_conds);
}