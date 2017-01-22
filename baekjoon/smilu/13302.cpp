#include <cstdio>

#define TICKET_CAP 50

int N, M;
bool disable[110] = {0};
int mc[110][TICKET_CAP]; // min cost

#define INF 0x3FFFFFFF

int min(int a, int b)
{
	return a < b ? a : b;
}

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i=0;i<M;++i) {
		int val;
		scanf("%d", &val);
		disable[val] = true;
	}
	for(int i=0;i<110;++i) {
		for(int j=0;j<TICKET_CAP;++j) {
			mc[i][j] = INF;
		}
	}
	mc[0][0] = 0;
	for(int i=0;i<=N;++i) {
		if(disable[i+1]) {
			for(int j=0;j<TICKET_CAP;++j) {
				mc[i+1][j] = min(mc[i+1][j], mc[i][j]);
			}
			continue;
		}
		for(int j=0;j<TICKET_CAP;++j) {
			if(mc[i][j] == INF) continue;
			if(j >= 3) {
				mc[i+1][j-3] = min(mc[i+1][j-3], mc[i][j]);
			}
			mc[i+1][j] = min(mc[i+1][j], mc[i][j] + 10000);
			mc[i+3][j+1] = min(mc[i+3][j+1], mc[i][j] + 25000);
			mc[i+5][j+2] = min(mc[i+5][j+2], mc[i][j] + 37000);
		}
	}
	int result = INF;
	for(int i=0;i<TICKET_CAP;++i) {
		result = min(result, mc[N][i]);
	}
	printf("%d", result);
	return 0;
}