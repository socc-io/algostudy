
#include <iostream>
#include <algorithm>

using namespace std;

#define INF 1000000000

int n, m, x;
int cost[1000][1000];

int main()
{
	scanf("%d%d%d", &n, &m, &x);
	--x;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			cost[i][j] = i == j ? 0 : INF;
		}
	}
	for(int i=0; i<m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		--a; --b;
		cost[a][b] = min(cost[a][b], c);
	}
	for(int k=0; k<n; ++k) {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				int new_cost = cost[i][k] + cost[k][j];
				if(new_cost < cost[i][j]) {
					cost[i][j] = new_cost;
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; ++i) {
		int new_ans = cost[i][x] + cost[x][i];
		if(new_ans > ans) ans = new_ans;
	}
	printf("%d", ans);

	return 0;
}