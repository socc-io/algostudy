#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

namespace io {
	const signed IS=100000;
	char I[IS+1],*J=I;

	inline void daer(){if(J>=I+IS-64){char*p=I;do*p++=*J++;while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
	template<int N=10,typename T=int>inline T getu(){daer();T x=0;int k=0;do x=x*10+*J-'0';while(*++J>='0'&&++k<N);++J;return x;}
	struct f{f(){I[read(0,I,IS)]=0;}}flu;
};

int n, h[100100], s[100100];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  n = io::getu();
  for (int i = 0; i < n; i++) h[i] = io::getu();
  for (int i = 1; i <= n; i++) s[i] = s[i-1] + h[i-1];

  int maxp = s[n-1] - h[0] + (*max_element(h+1, h+(n-1)));
  int p1 = (s[n] << 1) - h[0];
  int p2 = s[n-1];
  for (int i = 1; i < n-1; i++)
    maxp = max(maxp, max(p1 - s[i+1] - h[i], p2 + s[i] - h[i]));
  cout << maxp;
}
