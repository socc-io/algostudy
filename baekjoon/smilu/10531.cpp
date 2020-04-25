#include <cmath>
#include <complex>
#include <vector>
#include <valarray>
#include <algorithm>
using namespace std;

typedef complex<double> cpx;
typedef vector<cpx> vec;
typedef valarray<cpx> c_array;

const double pi = acos(-1);

// f.size()가 2의 승수여야 함
void fft(vec &f, bool inv = false){
    int n = f.size();
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

void fit_resize(vec &p) {
  int n = 1;
	while (n <= p.size()) n <<= 1;
	n <<= 1;
  p.resize(n);
}

void mul(vec &p){
  fit_resize(p);
  int n = p.size();
	fft(p);
	for (int i = 0; i < n; i++) p[i] = p[i] * p[i];
	fft(p, 1);
}

int main(void)
{
  int n, m, ans = 0;
  vec p(200001);
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp);
    p[tmp] = cpx(1, 0);
  }
  p[0] = cpx(1, 0);
  mul(p);
  scanf("%d", &m);
  while (m--) {
    int tmp; scanf("%d", &tmp);
    if (round(p[tmp].real()) > 0) ++ans;
  }
  printf("%d\n", ans);
}
