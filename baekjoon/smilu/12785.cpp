#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

#define MODULAR_BASE 1000007

int pow(int a, int b) {
	int res = 1;
	while(b > 0) {
		if((b&1) == 1) {
			res *= a;
			res %= MODULAR_BASE;
		}
		res *= res;
		res %= MODULAR_BASE;
		b >>= 1;
	}
	return res;
}

int facto(int n) {
   int res = 1;
   for(int i=2;i<=n;++i) {
   	res = (res * i) % MODULAR_BASE;
   }
   return res;
}

int f(int n, int m) {
	int low = ((facto(n)%MODULAR_BASE) * (facto(m)%MODULAR_BASE)) % MODULAR_BASE;
	int low_ = pow(low, MODULAR_BASE-2);
   return ((facto(n + m)%MODULAR_BASE)*low_)%MODULAR_BASE;
}

int main() {
   int w, h;
   int x, y;
   cin >> w >> h >> x >> y;
   int result = ((f(w - x, h - y)%MODULAR_BASE)*(f(x - 1, y - 1)% MODULAR_BASE)) % MODULAR_BASE;
   cout << result;
   return 0;
}