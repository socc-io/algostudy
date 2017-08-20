#include <cstdio>
#include <vector>

using namespace std;

#define INF 0x7FFFFFFF

int N, M;
int target[2];

vector<int> neigh[100];
bool visit[100];

int get_distance(int pos)
{
	if(pos == target[1]) {
		return 0;
	}
	
	visit[pos] = true;
	int min_dist = INF;
	for(auto it = neigh[pos].begin(); it != neigh[pos].end(); ++it) {
		int v = *it;
		if(visit[v]) continue;
		int dist = get_distance(v);
		if(dist < min_dist) {
			min_dist = dist;
		}
	}
	visit[pos] = false;

	return min_dist == INF ? INF : min_dist + 1;
}

int main(void)
{
	scanf("%d%d%d%d", &N, target, target + 1, &M);

	target[0]--;
	target[1]--;

	for(int i = 0; i < M; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;
		neigh[a].push_back(b);
		neigh[b].push_back(a);
	}

	int ans = get_distance(target[0]);
	ans = ans == INF ? -1 : ans;
	printf("%d", ans);

	return 0;
}