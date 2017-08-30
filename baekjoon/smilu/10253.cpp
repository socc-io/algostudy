#include <cstdio>
int main()
{
	int T,a,b,c;
	for(scanf("%d", &T); T--;) {
		scanf("%d%d",&a,&b);
		while(a){c=(a+b-1)/a;a=a*c-b;b*=c;}
		printf("%d\n",c);
	}
}