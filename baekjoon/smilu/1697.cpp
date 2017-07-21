#include <cstdio>
#include <queue>

int min_cost[100001];

#define INF (0x7FFFFFFF)

int main(void)
{
	for(int i=0; i<100001; ++i) {
		min_cost[i] = INF;
	}

	int src, dest;
	scanf("%d%d", &src, &dest);

	std::queue<int> Q;
	Q.push(src);
	min_cost[src] = 0;

	while(!Q.empty()) {
		int f = Q.front(); Q.pop();
		int c = min_cost[f];
		int k;

		if(f == dest) {
			printf("%d", c);
			return 0;
		}

		if(f < dest) {
			k = f << 1;
			if(k <= 100000 && min_cost[k] == INF) {
				Q.push(k);
				min_cost[k] = c + 1;
			}
		}

		k = f + 1;
		if(k <= 100000 && min_cost[k] == INF) {
			Q.push(k);
			min_cost[k] = c + 1;
		}

		k = f - 1;
		if(k <= 100000 && min_cost[k] == INF) {
			Q.push(k);
			min_cost[k] = c + 1;
		}
	}

}