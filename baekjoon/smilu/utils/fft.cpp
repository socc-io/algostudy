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

/*
input : f => Coefficient, w => principal n-th root of unity
output : f => f(x_0), f(x_1), f(x_2), ... , f(x_n-1)
T(N) = 2T(N/2) + O(N)
*/
void FFT(vec &f, cpx w){
	int n = f.size();
	if(n == 1) return; //base case
	vec even(n >> 1), odd(n >> 1);
	for(int i=0; i<n; i++){
		if(i & 1) odd[i >> 1] = f[i];
		else even[i >> 1] = f[i];
	}
	FFT(even, w*w); FFT(odd, w*w);
	cpx wp(1, 0);
	for(int i=0; i<n/2; i++){
		f[i] = even[i] + wp * odd[i];
		f[i+n/2] = even[i] - wp * odd[i];
		wp *= w;
	}
}

/*
input : a => A's Coefficient, b => B's Coefficient
output : A * B
*/
vec mul(vec a, vec b){
	int n = 1;
	while(n <= a.size() || n <= b.size()) n <<= 1;
	n <<= 1;
	a.resize(n); b.resize(n); vec c(n);
	cpx w(cos(2*pi/n), sin(2*pi/n));
	FFT(a, w); FFT(b, w);
	for(int i=0; i<n; i++) c[i] = a[i] * b[i];
	FFT(c, cpx(1, 0) / w);
	for(int i=0; i<n; i++){
		c[i] /= cpx(n, 0);
		c[i] = cpx(round(c[i].real()), round(c[i].imag())); //result is integer
	}
	return c;
}

// f.size()가 2의 승수여야 함
void fft(c_array &f, bool inv = false){
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
