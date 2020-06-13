#include <bits/stdc++.h>
using namespace std;

int v[100001];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i <= n; i++) v[i] += v[i-1];
  while (m--) {
    int a, b; cin >> a >> b;
    cout << v[b] - v[a-1] << '\n';
  }
}
