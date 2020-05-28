#include <bits/stdc++.h>
using namespace std;

int n;
double x[1000];
double y[1000];
double mx[1000];
double mn[1000];

double get_dist(int i, int j) {
  double dx = x[i] - x[j];
  double dy = y[i] - y[j];
  return sqrt(dx*dx + dy*dy);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
    mx[i] = 0.0;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double dst = get_dist(i, j);
      mx[i] = max(mx[i], dst);
      mx[j] = max(mx[j], dst);
    }
  }
  int ans = 0;
  double tmp = mx[0];
  for (int i = 1; i < n; i++) {
    if (mx[i] + mn[i] < tmp) {
      ans = i;
      tmp = mx[i];
    }
  }
  cout << x[ans] << ' ' << y[ans] << '\n';
}
