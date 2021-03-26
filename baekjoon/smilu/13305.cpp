#include <bits/stdc++.h>
using namespace std;

int n;
long long d[100010];
long long w[100010];

int main() {
  cin.tie(0); ios::sync_with_stdio(0);
  cin >> n;
  long long cost = 0;
  long long min_w = 0x3f3f3f3f;
  for (int i = 0; i < n-1; i++) cin >> d[i];
  for (int i = 0; i < n  ; i++) cin >> w[i];
  for (int i = 0; i < n-1; i++) {
    min_w = min(min_w, w[i]);
    cost += d[i] * min_w;
  }
  cout << cost << '\n';
}
