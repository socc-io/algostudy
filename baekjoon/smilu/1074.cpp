#include <cstdio>
int N,x,y,s;
int main(void)
{
	while(~scanf("%d%d%d",&N,&x,&y))
	{
		for(N=1<<N-1, s=0; N; N >>= 1) {
			if (x >= N) {
				s += (N*N)<<1;
				x -= N;
			}
			if (y >= N) {
				s += N*N;
				y -= N;
			}
		}
		printf("%d\n",s);
	}
}