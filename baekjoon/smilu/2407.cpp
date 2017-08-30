#include <cstdio>

#define K 100000000000000000

int n, m;

struct Big
{
	unsigned long long a, b;
	Big(): a(0), b(0) {}
	Big(unsigned long long a, unsigned long long b): a(a), b(b) {}
	void print()
	{
		if(a) {
			printf("%llu", a);
			unsigned long long tmp = b;
			int b_len = 0;
			while(tmp) {
				++b_len;
				tmp /= 10;
			}
			for(int i = 0; i < 17-b_len; ++i) {
				putchar('0');
			}
		}
		printf("%llu", b);
	}
	bool zero() { return a == 0 && b == 0; }
	Big operator+(const Big A) const {
		Big res;
		res.a = a + A.a;
		res.b = (b + A.b) % K;
		res.a += (b + A.b) / K;
		return res;
	}
};

Big mem[101][101];

Big get(int n, int m)
{
	if(n - m < m) m = n - m;
	if(m == 0) return Big(0, 1);
	if(!mem[n][m].zero()) return mem[n][m];
	mem[n][m] = get(n-1, m-1) + get(n-1, m);
	return mem[n][m];
}

int main(void)
{
	scanf("%d%d", &n, &m);

	get(n, m).print();
}