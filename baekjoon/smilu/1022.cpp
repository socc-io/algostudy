#include <stdio.h>

using namespace std;

int abs(int val) {
	return val < 0 ? (-1)*val : val;
}

int max(int a, int b)
{
	return a < b ? b : a;
}

int getValue(int x, int y){
	if(x == 0 && y == 0) return 1;
	int ax = abs(x); int ay = abs(y);
	int level = max(ax, ay);
	int c1 = 1;
	int c2;
	int fdelta;
	if(ax >= ay) {
		fdelta = y * (x / ax);
		if(x > 0) {
			c2 = 8;
		}
		else {
			c2 = 4;
		}
	}
	else {
		fdelta = x * (y / ay) * (-1);
		if(y > 0) {
			c2 = 2;
		}
		else {
			c2 = 6;
		}
	}
	for(int i=1; i<level; ++i) {
		int c3 = c2*2 - c1 + 8;
		c1 = c2;
		c2 = c3;
	} 
	c2 += fdelta;
	return c2;
}

int main(int argc, char** argv)
{
	int c1, r1, c2, r2;
	scanf("%d %d %d %d", &c1, &r1, &c2, &r2);
	for(int x=c1; x<=c2; ++x) {
		for(int y=r1; y<=r2; ++y) {
			printf("%3d ", getValue(x,y));
		}
		printf("\n");
	}
	return 0;
}