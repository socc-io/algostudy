
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

#define INF 1234567890

int n, m, r;
int a[101];
int c[101][101];

int main(void) {

	for(int i=0; i<101; ++i) for(int j=0; j<101; ++j) {
		c[i][j] = INF;
	}

	scanf("%d%d%d", &n, &m, &r);
	for(int i=0; i<n; ++i) {
		scanf("%d", a + i);
	}
	for(int i=0; i<r; ++i) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		--from; --to;
		c[from][to] = weight;
		c[to][from] = weight;
	}

	int max_a = 0;
	for(int i=0; i<n; ++i) {
		int now_a = 0;
		priority_queue<pii, vector<pii>, greater<pii>> Q;
		vector<int> dist(n, INF);
		vector<bool> visit(n, false);
		dist[i] = 0;
		Q.push(make_pair(0, i));
		while(!Q.empty()) {
			int now = Q.top().second;
			int now_cost = Q.top().first;
			Q.pop();
			if(visit[now]) continue;
			visit[now] = true;
			now_a += a[now];
			for(int next=0; next<n; ++next) {
				if(c[now][next] >= INF) continue;
				int next_cost = now_cost + c[now][next];
				if(next_cost < dist[next]) {
					dist[next] = next_cost;
					Q.push(make_pair(next_cost, next));
				}
			}
		}
		if(max_a < now_a) max_a = now_a;
	}

	printf("%d", max_a);

	return 0;
}