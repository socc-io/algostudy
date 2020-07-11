#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

ll inspect_fact(ll a, ll t) {
  ll ret = 0;
  ll k = t;
  while (a / k) {
    ret += a / k;
    k *= t;
  }
  return ret;
}

int inspect(ll a, ll t) {
  int ret = 0;
  while (a%t == 0) {
    ++ret;
    a /= t;
  }
  return ret;
}

ll pow(ll a, ll b) {
  ll ret = 1;
  while (b) {
    if (b&1) ret *= a;
    a = a*a;
    b >>= 1;
  }
  return ret;
}

ll m, ans;
vector<pair<ll,ll>> divs;
bool visit[100001];

void dfs(ll now) {
  ans = max(ans, now);
  for (auto &d: divs) {
    ll nxt = now * d.first;
    if (nxt > m) break;
    if (d.second <= 0) continue;
    if (visit[nxt]) continue;
    visit[nxt] = true;
    d.second--;
    dfs(nxt);
    d.second++;
  }
}

int solve() {
  ll s, f; cin >> s >> f >> m;
  Sieve sieve(m);
  const ll sf = s+f;
  for (int i = 2; i <= m; i++) {
    if (!sieve.get(i)) continue;
    ll c = inspect_fact(sf, i) - inspect_fact(s, i) - inspect_fact(f, i);
    divs.emplace_back(i, c);
  }
  dfs(1);
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve() << '\n';
}
