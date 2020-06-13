#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (int &v: a) cin >> v;

  vector<pi> s(n);
  for (int i = 0; i < n; i++) s[i].first = a[i];
  for (int i = 0; i < n; i++) s[i].second = i;
  sort(s.begin(), s.end());

  for (int i = 1; i <= n; i++) bit.update(i, 1);

  long long ret = 0;
  for (int i = 0; i < n; i++) {
    int pos = s[i].second;
    ret += bit.query(pos);
    bit.update(pos+1, -1);
  }
  cout << ret << '\n';
}
