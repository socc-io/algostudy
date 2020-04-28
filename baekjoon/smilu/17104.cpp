#include <cstdio>
#include <cmath>
#include <complex>
#include <vector>
#include <valarray>
#include <algorithm>
using namespace std;

const int SZ = 1<<21;

typedef complex<double> cpx;
typedef vector<cpx> vec;

const double pi = acos(-1);

// f.size()가 2의 승수여야 함
void fft(cpx f[], bool inv = false){
    const int n = SZ;
    for(int i = 1, j = 0; i < n; ++i){
        int b = n/2;
        while(!((j ^= b) & b)) b /= 2;
        if(i < j) swap(f[i], f[j]);
    }
    for(int k = 1; k < n; k *= 2){
        double a = (inv ? M_PI/k : -M_PI/k);
        cpx w(cos(a), sin(a));
        for(int i = 0; i < n; i += k*2){
            cpx wp(1, 0);
            for(int j = 0; j < k; ++j){
                cpx x = f[i+j], y = f[i+j+k] * wp;
                f[i+j] = x + y;
                f[i+j+k] = x - y;
                wp *= w;
            }
        }
    }
    if(inv){
        for(int i = 0; i < n; ++i)
            f[i] /= n;
    }
}

void mul(cpx p[]){
  fft(p);
	for (int i = 0; i < SZ; i++) p[i] *= p[i];
	fft(p, 1);
}

bool p[SZ>>1];
cpx a[SZ];

int main(void)
{
  p[0] = p[1] = true;
  for (long long i = 2; i < 1000000; i++) {
    if (p[i]) continue;
    a[i] = cpx(1, 0);
    for (long long j = i*i; j < 1000000; j+=i) {
      p[j] = true;
    }
  }
  mul(a);
  int t; scanf("%d", &t);
  while (t--) {
    int v; scanf("%d", &v);
    int r = round(a[v].real()), h = v/2;
    int e = !p[h];
    if (h%2 == 0 && h > 2) e = 0;
    if (e) --r;
    printf("%d\n", r/2+e);
  }
}
