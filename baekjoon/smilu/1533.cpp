#include <cstdio>
#include <vector>
using namespace std;

#define MOD 1000003

typedef long long lld;
typedef vector<lld> vi;
typedef vector<vi> vvi;

class Matrix {
public:
  int n;
  vvi vs;
  Matrix() { n = 0; }
  Matrix(int _n) {
    n = _n;
    vs = vvi(n, vi(n));
  }
  Matrix operator * (const Matrix &b) const {
    Matrix r(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        r.vs[i][j] = 0;
        for (int k = 0; k < n; k++) {
          r.vs[i][j] = (r.vs[i][j] + vs[i][k] * b.vs[k][j]) % MOD;
        }
      }
    }
    return r;
  }
  Matrix pow(int p) const {
    Matrix r(n);
    if (p == 0) {
      for (int i = 0; i < n; i++) r.vs[i][i] = 1;
      return r;
    }
    if (p == 1) {
      return (*this);
    }
    Matrix h = pow(p/2);
    r = h * h;
    if (p & 1) r = r * (*this);
    return r;
  }
};

int main(void)
{
  int n, s, e, t;
  char buf[11];
  scanf("%d%d%d%d", &n, &s, &e, &t);
  Matrix A(5*n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      A.vs[i*5+j+1][i*5+j] = 1;
    }
  }
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    for (int j = 0; j < n; j++) {
      int v = buf[j] - '0';
      if (v == 0) continue;
      A.vs[i*5][j*5+v-1] = 1;
    }
  }
  Matrix R = A.pow(t);
  printf("%lld", R.vs[s*5-5][e*5-5]);
}
