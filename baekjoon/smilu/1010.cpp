#include <iostream>

using namespace std;

long long combination(int a, int b)
{
	if(b > (a >> 1)) {
		b = a - b;
	}
	long long mul = 1;
	long long div = 1;
	for(int i=2; i<=b; ++i){
		div *= i;
	}
	for(int i=a; i>a-b; --i){
		mul *= i;
	}
	return mul / div;
}

int main(void)
{
	int n, m, T;
	cin >> T;
	for(int test_idx = 0; test_idx < T; ++test_idx)
	{
		cin >> n >> m;
		printf("%lld\n", combination(m,n));
	}
	return 0;
}