#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 22;
const ll mod = 1000000007;

struct Mat {
  ll v[MAX_N][MAX_N];
  Mat operator*(const Mat &b) const {
    Mat ret(0);
    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        for (int k = 0; k < MAX_N; k++) {
          ret.v[i][j] += v[i][k] * b.v[k][j];
          ret.v[i][j] %= mod;
        }
      }
    }
    return ret;
  }
  void set(const int k) {
    memset(this, 0x00, sizeof(Mat));
    for (int i = 0; i < MAX_N; i++) v[i][i] = k;
  }
  void print(int n) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cout << v[j][i] << ' ';
      } cout << '\n';
    }
  }
  Mat(){}
  Mat(int k){set(k);}
};

Mat pow(Mat b, int p) {
  Mat ret(1);
  while (p) {
    if (p&1) {
      ret = ret * b;
    }
    b = b*b;
    p >>= 1;
  }
  return ret;
}

int t, n, d;
Mat adj[101];
Mat prod[101];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> t >> n >> d;
  for (int i = 1; i <= t; i++) {
    int m; cin >> m;
    for (int j = 0; j < m; j++) {
      int a, b, c; cin >> a >> b >> c;
      adj[i].v[b][a] = c;
    }
  }
  Mat ans(1);
  prod[1] = adj[1];
  for (int i = 2; i <= t; i++) {
    prod[i] = adj[i] * prod[i-1];
  }
  ans = pow(prod[t], d/t) * ans;
  int rem = d%t;
  if (rem) ans = prod[rem] * ans;
  ans.print(n);
}
