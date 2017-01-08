#include <cstdio>

int e[1000001];
long long p[1000001];
int n, m, k;

long long my_sum(int idx)
{
	long long sum = 0;
	while(idx > 0) {
		sum += p[idx];
		idx -= (idx & -idx);
	}
	return sum;
}

void make()
{
	for(int i=1;i<=n;++i) {
		int l = (i & -i);
		p[i] = my_sum(i-1) - my_sum(i-l) + (long long)e[i];
	}
}

void update(int idx, int val)
{
	int diff = val - e[idx];
	e[idx] = val;
	while(idx <= n) {
		p[idx] += diff;
		idx += (idx & -idx);
	}
}

void print_sum(int from, int to)
{
	printf("%llu\n", my_sum(to) - my_sum(from-1));
}

int main(void)
{
	scanf("%d%d%d", &n,&m,&k);
	for(int i=1;i<=n;++i) {
		scanf("%d", e+i);
	}
	make();
	int mk = m + k;
	for(int i=0;i<mk;++i) {
		int a, b, c;
		scanf("%d%d%d", &a,&b,&c);
		if(--a) {
			print_sum(b,c);
		}
		else {
			update(b,c);
		}
	}
}