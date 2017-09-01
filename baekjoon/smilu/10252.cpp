#include <cstdio>

int main()
{
	int T, m, n;
	for(scanf("%d", &T); T--;) {
		scanf("%d%d", &m, &n);
		puts("1\n(0,0)");
		for(int y=0;y<n;++y) {
			if(y&1) for(int x=m-1;x>=1;--x) printf("(%d,%d)\n",x,y);
			else for(int x=1;x<m;++x) printf("(%d,%d)\n",x,y);
		}
		for(int y=n-1;y>=1;--y) printf("(0,%d)\n",y);
	}
}
