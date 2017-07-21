#include <cstdio>
#include <cstring>

int N, M, NM;

int track[26][2];
bool visit[26][26];
int dir[8][2] = {-2,-1, -2,1, -1,-2, -1,2, 1,-2, 1,2, 2,-1, 2,1};

int depth;

bool search(int x, int y)
{
	if(visit[x][y] || x < 0 || x >= N || y < 0 || y >= M) return false;

	track[depth][0] = x;
	track[depth][1] = y;

	if(depth == NM - 1) return true;

	visit[x][y] = true;
	depth++;

	for(int i=0; i<8; ++i) {
		if(search(x + dir[i][1], y + dir[i][0])) {
			return true;
		}
	}

	visit[x][y] = false;
	depth--;

	return false;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for(int ti=0; ti<T; ++ti) {
		scanf("%d%d", &N, &M);
		NM = N * M;
		printf("Scenario #%d:\n", ti + 1);

		memset(visit, false, sizeof(visit));

		depth = 0;
		bool found = search(0, 0);

		// for(int i=0; i<N; ++i) {
		// 	for(int j=0; j<M; ++j) {
		// 		if(search(i, j, 0)) {
		// 			found = true;
		// 			break;
		// 		}
		// 	}
		// 	if(found) break;
		// }

		if(found) {
			for(int i=0; i<NM; ++i) {
				printf("%c%d", 'A' + track[i][1], track[i][0] + 1);
			} printf("\n");
		} else{
			printf("impossible\n");
		}

		if(ti != T - 1) {
			printf("\n");
		}
	}
	return 0;
}