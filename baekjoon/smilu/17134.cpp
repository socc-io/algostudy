#include <cstdio>
#include <cmath>
#include <complex>
#include <valarray>
using namespace std;

#define MAX_N 1000000
#define SZ (1<<21)

typedef complex<double> cpx;
typedef valarray<cpx> c_array;

const double pi = acos(-1);

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

inline bool is_odd(int x) { return (x & 1) > 0; }

int main(void)
{
	valarray<int> chk(SZ/2);
	c_array f(SZ), g(SZ);
	chk[0] = chk[1] = 1;
	for (int i = 2; i < MAX_N; i++) {
		if (chk[i]) continue;
		if (is_odd(i)) f[i] = cpx(1, 0);
		for (int j = i+i; j < MAX_N; j += i) {
			chk[j]++;
			if (j/i%i == 0) {
				chk[j]++;
				if (j/i/i%i == 0) chk[j]++;
			}
		}
	}
	for (int i = 2; i < MAX_N; i += 2) {
		if (chk[i] == 2) g[i] = cpx(1, 0);
	}

	fft(f);
	fft(g);
	for (int i = 0; i < SZ; i++) f[i] *= g[i];
	fft(f, true);

	int t; scanf("%d", &t);
	while (t--) {
		int x; scanf("%d", &x);
		printf("%d\n", (int)round(f[x].real()));
	}
}
