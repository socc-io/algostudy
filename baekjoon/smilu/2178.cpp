#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

#define INF 0xFFFFFF

int N, M;
char map[101][101];
int cost[101][101];

int nextOff[4][2] = {
	{1,0},
	{-1,0},
	{0,1},
	{0,-1}
};

void bfs()
{
	queue<pair<int ,int> > Q;
	Q.push(make_pair(0,0));
	while(!(Q.empty())) {
		pair<int,int> pos = Q.front();
		Q.pop();
		int now_cost = cost[pos.first][pos.second];
		for(int i=0; i<4; ++i) {
			pair<int,int> ne(pos.first + nextOff[i][0], pos.second + nextOff[i][1]);
			if(ne.first < 0 || N <= ne.first || ne.second < 0 || M <= ne.second) continue;
			if(map[ne.first][ne.second] == '0') continue;
			if(cost[ne.first][ne.second] != INF) continue;
			cost[ne.first][ne.second] = now_cost+1;
			Q.push(ne);
		}
	}
}

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) {
		scanf("%s", map[i]);
	}
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			cost[i][j] = INF;
		}
	}
	cost[0][0] = 1;
	bfs();
	printf("%d", cost[N-1][M-1]);
}