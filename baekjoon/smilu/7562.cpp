#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

int N;
int tile[301][301];
int startX, startY;
int endX, endY;

typedef pair<int, int> pos;

int nextOffset[][2] = {
	{2,-1},{2,1},
	{-2,-1},{-2,1},
	{1,2},{1,-2},
	{-1,2},{-1,-2}
};

void run()
{
	scanf("%d%d%d%d%d", &N, &startX, &startY, &endX, &endY);
	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) tile[i][j] = -1;

	tile[startX][startY] = 0;
	queue<pos> q;
	q.push(make_pair(startX, startY));

	bool metDest = false;

	while( !(q.empty()) && !metDest ) {
		pos f = q.front(); q.pop();
		int nextCost = tile[f.first][f.second] + 1;
		for(int i=0; i<8; ++i) {
			pos n = make_pair(f.first + nextOffset[i][0], f.second + nextOffset[i][1]);
			if(n.first < 0 || n.first >= N || n.second < 0 || n.second >= N) continue;
			if(tile[n.first][n.second] != -1) continue;
			tile[n.first][n.second] = nextCost;
			q.push(n);

			if(n.first == endX && n.second == endY) {
				metDest = true;
				break;
			}
		}
	}

	printf("%d\n", tile[endX][endY]);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		run();
	}
}