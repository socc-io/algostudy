#include <cstdio>
#include <cstdlib>

int GCD(int u, int v)
{
	int t;
	while(v) {
		t = u%v;
		u = v;
		v = t;
	}
	return u;
}

int main(void)
{
	char buffer[20];
	int a, b;
	scanf("%s", buffer);
	for(int div=0; div<20; ++div) {
		if(buffer[div] == ':') {
			buffer[div] = '\0';
			a = atoi(buffer); 
			b = atoi(buffer+div+1);
			break; 
		}
	}
	int g = GCD(a, b); 
	printf("%d:%d", a/g, b/g);
	return 0;
}