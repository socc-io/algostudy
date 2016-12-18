#include <cstdio>
#include <algorithm>

#define INF 0x3FFFFFFF

struct point
{
	int x;
	int y;
};

long long abs(long long val) {
	return (val < 0 ? -val : val);
}

int rotation[24][4] = {
	{0,1,2,3},
	{0,1,3,2},
	{0,2,1,3},
	{0,2,3,1},
	{0,3,1,2},
	{0,3,2,1},
	{1,0,2,3},
	{1,0,3,2},
	{1,2,0,3},
	{1,2,3,0},
	{1,3,0,2},
	{1,3,2,0},
	{2,0,1,3},
	{2,0,3,1},
	{2,1,0,3},
	{2,1,3,0},
	{2,3,0,1},
	{2,3,1,0},
	{3,0,1,2},
	{3,0,2,1},
	{3,1,0,2},
	{3,1,2,0},
	{3,2,0,1},
	{3,2,1,0}
};

int main(int argc, char** argv)
{
	point p[4];
	int k[8];
	for(int i=0;i<4;++i) {
		int x, y;
		scanf("%d%d", &x,&y);
		p[i].x = x;
		p[i].y = y;
	}
	long long min_f = -1;
	long long min_min_x = -1;
	for(int ri=0;ri<24;++ri) {
		int* rot = rotation[ri];
		int pi1 = rot[0], pi2 = rot[1], pi3 = rot[2], pi4 = rot[3];
		k[0] =   p[pi1].x ; k[1] =   p[pi1].y ;
		k[2] =   p[pi2].x ; k[3] = -(p[pi2].y);
		k[4] = -(p[pi3].x); k[5] =   p[pi3].y ;
		k[6] = -(p[pi4].x); k[7] = -(p[pi4].y);
		std::sort(k, k+8);
		long long min_x = k[4];
		long long f = 0;
		for(int i=0;i<8;++i) {
			f += abs((long long)min_x - k[i]);
		}
		// printf("{%d,%d,%d,%d}: %d, %lld\n", pi1, pi2, pi3, pi4, min_x, f);
		if(min_f > f || min_f == -1) {
			min_f = f;
			min_min_x = min_x * 2;
		}
	}
	printf("%lld",abs(min_min_x));
}