#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

int N;
int N2;
int x[20];
int y[20];
bool prevC[20];
bool nowC[20];

int now_x;
int now_y;
double now_dist;
double min_dist;

double getDist(double a, double b)
{
	return sqrt(a*a + b*b);
}
void copyC(bool* to, bool* from) {
	for(int i=0; i<N; ++i) to[i] = from[i];
}

void run()
{
	scanf("%d", &N);
	N2 = N>>1;
	for(int i=0; i<N; ++i) {
		scanf("%d%d", x+i, y+i);
	}
	now_x=0; now_y=0;
	for(int i=0; i<N2; ++i) { // first half are end points
		now_x += x[i];
		now_y += y[i];
	}
	for(int i=N2; i<N; ++i) { // last half are start points
		now_x -= x[i];
		now_y -= y[i];
	}
	now_dist = getDist(now_x, now_y);
	min_dist = now_dist;

	for(int i=0; i<N2; ++i) prevC[i] = false;
	for(int i=N2; i<N; ++i) prevC[i] = true;
	copyC(nowC, prevC);
	while(std::next_permutation(nowC, nowC+N)) {
		for(int i=0; i<N; ++i) {
			if(prevC[i] != nowC[i]) {
				now_x += (x[i]<<1) * (prevC[i] ? 1 : -1);
				now_y += (y[i]<<1) * (prevC[i] ? 1 : -1);
			}
		}
		now_dist = getDist(now_x, now_y);
		min_dist = now_dist < min_dist ? now_dist : min_dist;
		copyC(prevC, nowC);
	}
	printf("%.6f\n", min_dist);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int test_idx=0; test_idx<T; ++test_idx) {
		run();
	}
	return 0;
}