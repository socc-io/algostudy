#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n, max = 0;
	int x[1000001], y[1000001] = {0,};
	scanf("%d",&n);
	for(int i=1; i <= n;i++) scanf("%d",&x[i]);
	for(int i=1; i <= n;i ++){
		y[x[i]] = y[x[i]-1] + 1;
		if(y[x[i]] > max) max = y[x[i]];
	}
	printf("%d", n-max);	

	return 0;
}
