#include <iostream>
#include <queue>
#include <vector>

#define INF 0x7FFFFFFF

using namespace std;

int N, K, M;

int tmp, tmp2, tmp3;

vector<int> neigh[101000];
int cost[101000];

int main(void)
{
	scanf("%d%d%d", &N, &K, &M);
	for(int i = 0; i < M; ++i) {
		int head = N + i;
		for(int j = 0; j < K; ++j) {
			scanf("%d", &tmp); --tmp;
			neigh[tmp].push_back(head);
			neigh[head].push_back(tmp);
		}
	}

	queue<int> Q;
	Q.push(0);

	for(int i = 0; i < N + M; ++i) {
		cost[i] = INF;
	}
	cost[0] = 0;

	bool found = false;
	while(!Q.empty()) {
		int w = Q.front();
		Q.pop();
		// printf("w: %d\n", w);
		for(auto it = neigh[w].begin(); it != neigh[w].end(); ++it) {
			int v = *it;
			if(cost[v] != INF) continue;
			// printf("    v: %d\n", v);
			cost[v] = cost[w] + 1;
			if(v == N - 1) {
				// printf("found!\n");
				found = true;
				break;
			}
			Q.push(v);
		}
		if(found) {
			break;
		}
	}

	printf("%d", cost[N - 1] == INF ? -1 : cost[N - 1] / 2 + 1);

	return 0;
}