#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

int M, N, H;

struct pos {
	int x, y, h;
	pos operator+(pos o) {
		pos res = {x+o.x, y+o.y, h+o.h};
		return res;
	}
};
pos make_pos(int x, int y, int h) {
	pos res = {x, y, h};
	return res;
}

void mat_clear(int*** mat, int x, int y, int z, int v)
{
	for(int i=0; i<x; ++i) for(int j=0; j<y; ++j) for(int k=0; k<z; ++k)
		mat[i][j][k] = v;
}

int tomato[100][100][100];
int cost[100][100][100];

pos offset[] = {
	{0,0,1},{0,0,-1},
	{0,1,0},{0,-1,0},
	{1,0,0},{-1,0,0}
};

int main(void)
{
	scanf("%d%d%d", &M, &N, &H);
	for(int h=0; h<H; ++h) for(int i=0; i<N; ++i) for(int j=0; j<M; ++j)
		scanf("%d", &(tomato[i][j][h]));
	for(int h=0; h<H; ++h) for(int i=0; i<N; ++i) for(int j=0; j<M; ++j)
		cost[i][j][h] = -1;

	queue<pos> q;

	for(int h=0; h<H; ++h) for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) {
		if(tomato[i][j][h] == 1) {
			q.push(make_pos(i, j, h));
			cost[i][j][h] = 0;
		}
	}

	int max_cost = -1;

	while( !(q.empty()) ) {
		pos f = q.front(); q.pop();
		int nextCost = cost[f.x][f.y][f.h] + 1;

		max_cost = max_cost > nextCost ? max_cost : nextCost;

		for(int i=0; i<6; ++i) {
			pos n = f + offset[i];
			if(n.x < 0 || n.y < 0 || n.h < 0 ||
				n.x >= N || n.y >= M || n.h >= H) {
				continue;
			}
			if(tomato[n.x][n.y][n.h] == 1) continue;
			if(tomato[n.x][n.y][n.h] == -1) continue;
			tomato[n.x][n.y][n.h] = 1;
			cost[n.x][n.y][n.h] = nextCost;
			q.push(n);
		}
	}

	bool all_ripe = true;

	for(int h=0; h<H; ++h) for(int i=0; i<N; ++i) for(int j=0; j<M; ++j) {
		if(tomato[i][j][h] == 0) {
			all_ripe = false;
			break;
		}
	}

	printf("%d", all_ripe ? max_cost-1 : -1);
}