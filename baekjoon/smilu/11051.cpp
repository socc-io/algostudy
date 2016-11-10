#include <stdio.h>

#define DIV 10007LL

long long pow(long long x, long long y)
{
	long long ans = 1;
	while(y > 0) {
		if((y&1) != 0) {
			ans = (ans * x) % DIV;
		}
		x = (x*x)  % DIV;
		y = y >> 1;
	}
	return ans;
}

int main(int argc, char** argv)
{
	long long a, b;
	scanf("%lld %lld", &a, &b);
	if(b > (a/2)) b = a - b;
	long long multiplier = 1;
	long long divider = 1;
	for(long long i=a-b+1; i<=a; ++i) {
		multiplier = (multiplier * i) % DIV;
	}
	for(long long i=2;i<=b;++i) {
		divider = (divider * i) % DIV;
	}
	long long div_reverse = pow(divider, DIV-2);
	div_reverse %= DIV;
	long long ans = (multiplier * div_reverse) % DIV;
	
	printf("%lld", ans);
	return 0;
}