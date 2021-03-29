#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000007;
const ll fibo_root_dat[] = {
  0,1,
  1,1,
};
const ll one_dat[] = {
  1,0,
  0,1,
};
const int mat_size = 2;

struct mat {
  ll v[mat_size][mat_size];
};

mat matmul(mat a, mat b) {
  mat res;
  memset(&res, 0x00, sizeof(mat));
  for (int i = 0; i < mat_size; i++) {
    for (int j = 0; j < mat_size; j++) {
      for (int k = 0; k < mat_size; k++) {
        res.v[i][j] += a.v[i][k] * b.v[k][j];
      }
      res.v[i][j] %= mod;
    }
  }
  return res;
}

mat one() {
  mat res;
  memcpy(&res, one_dat, sizeof(one_dat));
  return res;
}

mat matpow(mat a, ll p) {
  mat res = one();
  while (p) {
    if (p & 1) {
      res = matmul(res, a);
    }
    a = matmul(a, a);
    p >>= 1;
  }
  return res;
}

mat fibo_root() {
  mat res;
  memcpy(&res.v, fibo_root_dat, sizeof(fibo_root_dat));
  return res;
}

int main() {
  ll p; cin >> p;
  cout << matpow(fibo_root(), p).v[0][1];
}
