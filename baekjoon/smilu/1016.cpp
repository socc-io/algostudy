#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull m, M, D;

bool prime_table[1000010];
bool nono[1000010];

int primes[1000010];
int primes_num;

int main(void)
{
	scanf("%llu%llu", &m, &M);
	D = M - m;

	primes_num = 0;
	for(ull i = 2; i*i <= M; ++i) {
		if(prime_table[i]) continue;
		primes[primes_num++] = i;
		for(ull j = i*2; j*j <= M; j += i) {
			prime_table[j] = true;
		}
	}

	int cnt = D + 1;
	for(int pit = 0; pit < primes_num; ++pit) {
		ull pp = primes[pit]; pp = pp * pp;
		for(ull cur = (((m + pp - 1) / pp) * pp) - m; cur <= D; cur += pp) {
			if(nono[cur]) continue;
			nono[cur] = true;
			--cnt;
		}
	}

	printf("%d\n", cnt);

	return 0;
}