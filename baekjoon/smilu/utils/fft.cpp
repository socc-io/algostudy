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

void fit_resize(vec &p, vec &q) {
  int n = 1;
	while (n <= p.size() || n <= q.size()) n <<= 1;
	n <<= 1;
  p.resize(n);
	q.resize(n);
}

vec mul(vec &p, vec &q){
  fit_resize(p, q);
  int n = p.size();
	vec c(n);
	fft(p); fft(q);
	for (int i = 0; i < n; i++) c[i] = p[i] * q[i];
	fft(c, 1);
	return c;
}
