#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

typedef complex<double> cpx;
typedef vector<cpx> vec;
typedef long long lld;

const double pi = acos(-1);

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

int main(void)
{
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<int> a(2*n), b(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) a[n+i] = a[i];
  for (int i = n-1; i >= 0; i--) cin >> b[i];

  vec va(2*n), vb(n);
  for (int i = 0; i < 2*n; i++) va[i] = cpx(a[i], 0);
  for (int i = 0; i < n  ; i++) vb[i] = cpx(b[i], 0);

  vec vc = mul(va, vb);

  lld ans = 0;
  for (int i = 0; i < vc.size(); i++) {
    ans = max<lld>(ans, round(vc[i].real()));
  }
  cout << ans << '\n';
}
