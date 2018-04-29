
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int p[1000];

int profit(int x)
{
	static int mem[1001];
	if(x < 0) return -99999;
	if(x == 0) return 0;
	if(mem[x] != 0) return mem[x];
	int &ret = mem[x];
	for(int i=0; i<n; ++i) {
		ret = max(ret, profit(x-i-1) + p[i]);
	}
	return ret;
}

int main(void)
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d", p + i);
	}
	printf("%d", profit(n));
	return 0;
}
