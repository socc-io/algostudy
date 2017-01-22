#include <stdio.h>

int n;
int sa[10001];

int qs(int k) // quick selection
{
	int start = 0;
	int end   = n-1;
	while(start < end) {
		int i = start;
		int j = end;
		int mid = sa[(i+j)>>1];
		while(i<j) {
			if(sa[i] >= mid) {
				int tmp = sa[i];
				sa[i] = sa[j];
				sa[j] = tmp;
				--j;
			} else {
				++i;
			}
		}
		if(sa[i] > mid) --i;
		if(k <= i) end = i;
		else start = i+1;
	}
	return sa[k];
}

int main(void)
{
	int s, a, i;
	scanf("%d", &n);
	if((n&1)) {
		putchar('1');
		return 0;
	}
	for(i=0;i<n;++i) {
		scanf("%d%d", &s, &a);
		sa[i] = a - s;
	}
	printf("%d", qs(n>>1) - qs((n>>1)-1) + 1);
	return 0;
}