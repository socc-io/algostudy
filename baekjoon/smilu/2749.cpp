#include <stdio.h>

#define DIV 1000000LL

template <class T>
void matmul(T *a, T *b, T *res)
{
	res[0] = (a[0] * b[0] + a[1] * b[2]) % DIV;
	res[1] = (a[0] * b[1] + a[1] * b[3]) % DIV;
	res[2] = (a[2] * b[0] + a[3] * b[2]) % DIV;
	res[3] = (a[2] * b[1] + a[3] * b[3]) % DIV;
}

template <class T>
void matcpy(T *from, T *to)
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
	to[3] = from[3];
}

int main(void)
{
	long long n;
	scanf("%lld", &n);
	long long fibo_basemat[4];
	fibo_basemat[0] = 0LL; fibo_basemat[1] = 1LL; fibo_basemat[2] = 1LL; fibo_basemat[3] = 1LL;
	long long fibo_pow[65][4];
	matcpy<long long>(fibo_basemat, fibo_pow[0]);
	int max_place = 62;
	long long place_finder = 1LL << 62;
	while((place_finder & n) == 0LL) {
		max_place--;
		place_finder = place_finder >> 1;
	}
	for(int i=1; i<=max_place; ++i) {
		matmul<long long>(fibo_pow[i-1], fibo_pow[i-1], fibo_pow[i]);
	}
	
	long long res[4] = {1, 0, 0, 1};
	long long tmpmat[4];
	for(int i=max_place; i>=0; --i) {
		if((place_finder & n) != 0LL) {
			matcpy<long long>(res, tmpmat);
			matmul<long long>(tmpmat, fibo_pow[i], res);
		}
		place_finder = place_finder >> 1;
	}

	printf("%lld", res[1]);
	return 0;
}