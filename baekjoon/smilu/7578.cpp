#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

const int MAX_N = 500050;

struct BIT {
  int ft[MAX_N];
  void update(int x, int v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  int query(int x) {
    int ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  int query(int a, int b) {
    return query(b) - query(a-1);
  }
} bit;

int n;
pi an[MAX_N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> an[i].first;
    an[i].second = i + 1;
  }
  sort(an, an + n);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    v = lower_bound(an, an + n, make_pair(v, 0))->second;
    ans += bit.query(v+1, n+1);
    bit.update(v, 1);
  }
  cout << ans << '\n';
}
