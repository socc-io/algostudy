#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

long long sub_answer_mem[21][21];

long long permutation(int n, int c)
{
	long long result = 1;
	for(int i=0; i<c; ++i) {
		result *= n-i;
	}
	return result;
}

long long combination(int n, int c)
{
	return permutation(n, c) / permutation(c, c-1);
}

long long sub_answer(int n, int l)
{
	if (sub_answer_mem[n][l] != -1) return sub_answer_mem[n][l];
	long long result = 0;
	for(int r=0; r<=n-l; ++r) {
		result += permutation(n-1, r)*sub_answer(n-1-r, l-1);
	}
	sub_answer_mem[n][l] = result;
	return result;
}

long long answer(int n, int l, int r)
{
	long long result = 0;
	for(int L=l-1; L<=n-r; ++L) {
		result += sub_answer(L, l-1)*sub_answer(n-1-L,r-1)*combination(n-1, L);
	}
	return result;
}

void run()
{
	int n, l, r;
	scanf("%d%d%d", &n, &l, &r); 
	printf("%lld\n", answer(n, l, r));
}

int main(void)
{
	for(int i=0; i<21; ++i) {
		for(int j=0; j<21; ++j) {
			sub_answer_mem[i][j] = -1;
			if(j==0) sub_answer_mem[i][j] = 0;
		}
	}
	sub_answer_mem[0][0] = 1;
	sub_answer_mem[1][0] = 0;
	sub_answer_mem[1][1] = 1;
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		run();
	}
	// printf("mem:\n");
	// for(int i=0; i<21; ++i) {
	// 	for(int j=0; j<21; ++j) {
	// 		printf("%lld ", sub_answer_mem[i][j]);
	// 	}
	// 	printf("\n");
	// }
	return 0;
}