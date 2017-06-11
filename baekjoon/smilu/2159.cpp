#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

typedef unsigned long long ull;

int abs(int val) { return val>0 ? val : -val; }

template <class T>
T mymin(T a, T b) {
	if(a == -1) return b;
	return a<b ? a:b;
}

struct pos {
	int x, y;
	pos operator+(pos o) {
		pos res = {x + o.x, y + o.y};
		return res;
	}
	int mdist(pos o) {
		return abs(x - o.x) + abs(y - o.y);
	}
};

int N;
pos points[100001];

ull dp[100001][5];

pos offset[] = {
	{0,0},{0,1},{0,-1},{1,0},{-1,0}
};

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<=N; ++i) {
		scanf("%d%d", &(points[i].x), &(points[i].y));
	}

	// first customer
	for(int i=0; i<5; ++i) {
		dp[1][i] = points[0].mdist(points[1] + offset[i]);
	}
	for(int i=2; i<=N; ++i) { // point cursor
		pos prev_pos = points[i-1];
		for(int j=0; j<5; ++j) { // error cursor
			pos now_pos = points[i] + offset[j];
			dp[i][j] = -1;
			for(int k=0; k<5; ++k) { // prev error cursor
				dp[i][j] = mymin(dp[i][j], dp[i-1][k] + (prev_pos + offset[k]).mdist(now_pos));
			}
		}
	}

	ull min_cost = -1;
	for(int i=0; i<5; ++i) {
		min_cost = mymin(min_cost, dp[N][i]);
	}

	printf("%llu\n", min_cost);
}