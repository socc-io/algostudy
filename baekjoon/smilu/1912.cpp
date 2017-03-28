#include <stdio.h>

int arr[100001];
int n;
int I[100001]; // including
int G[100001]; // global

int main(int argc, char** argv)
{
	scanf("%d", &n);
	for(int i=0;i<n;++i) scanf("%d", arr+i);
	G[0] = arr[0];
	I[0] = arr[0];
	for(int i=1;i<n;++i) {
		I[i] = I[i-1] < 0 ? arr[i] : I[i-1]+arr[i];
		G[i] = I[i] > G[i-1] ? I[i] : G[i-1];
	}
	printf("%d\n",G[n-1]);
}