#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define LL_INF 0x7FFFFFFFFFFFFFFF

int inp[8];
int buffer[8];
int targeter[] = {1, 1, 1, -1, -1, 1, -1, -1};
int perm[] = {0, 1, 2, 3};

long long min_cost = LL_INF;
long long min_width;

inline long long abss(long long val)
{
	return val > 0 ? val : -val;
}

int main(void)
{
	for(int i=0; i<8; ++i) {
		scanf("%d", inp + i);
		inp[i] <<= 1;
	}

	do {

		for(int i=0; i<4; ++i) {
			buffer[i * 2] = inp[perm[i] * 2];
			buffer[i * 2 + 1] = inp[perm[i] * 2 + 1];
		}

		for(int i=0; i<8; ++i) {
			buffer[i] *= targeter[i];
		}

		sort(buffer, buffer + 8);

		long long cost = 0;
		long long width = buffer[4] >= 1 ? buffer[4] : 1;

		for(int i=0; i<8; ++i) {
			cost += abss(width - buffer[i]);
		}

		if(min_cost > cost || (min_cost == cost && min_width < width)) {
			min_cost = cost;
			min_width = width;
		}
		
	} while(next_permutation(perm, perm + 4));

	printf("%lld", min_width);
}