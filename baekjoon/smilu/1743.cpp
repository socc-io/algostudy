#include <cstdio>
#include <cstdlib>
#include <cstring>

int width, height, N;
int x[10000];
int y[10000];
int tile[101][101];
int group_index = 1;

int getSize(int a, int b)
{
	int s = 1;
	if(tile[a][b] == 0) return 0;
	tile[a][b] = 0;
	if (a > 1   ) s += getSize(a-1,b);
	if (a < 100 ) s += getSize(a+1,b);
	if (b > 1   ) s += getSize(a,b-1);
	if (b < 100 ) s += getSize(a,b+1);
	return s;
}

int main(void)
{
	scanf("%d%d%d", &width, &height, &N);
	memset(tile, 0, 101*101*sizeof(bool));
	for(int i=0;i<N;++i) {
		scanf("%d%d", &x[i], &y[i]);
		tile[x[i]][y[i]] = -1;
	}
	int max_size = -1;
	for(int i=0;i<N;++i) {
		int size = getSize(x[i], y[i]);
		if (max_size < size) {
			max_size = size;
		}
	}
	// for(int i=0;i<101;++i) {
	// 	for(int j=0;j<101;++j) {
	// 		printf("%d ", tile[i][j]);
	// 	}
	// 	printf("\n");
	// }
	printf("%d\n", max_size);
	return 0;
}