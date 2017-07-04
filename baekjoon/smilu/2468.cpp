#include <cstdio>

int N;
int height[100][100];

int group[100][100];
int group_idx = 0;

int offsets[][2] = {
	{1, 0},
	{-1,0},
	{0, 1},
	{0,-1}
};

int try_group(int x, int y, int h, int value)
{
	if(x < 0 || x >= N || y < 0 || y >= N) return 0;  // range check
	if(height[x][y] <= h) return 0;  // height check
	if(group[x][y] != -1) return 0;  // visit check

	group[x][y] = value;
	for(int offset_idx=0; offset_idx<4; ++offset_idx) {
		int nx = x + offsets[offset_idx][0];  // neighbor x
		int ny = y + offsets[offset_idx][1];  // neighbor y
		try_group(nx, ny, h, value);
	}
	return 1;
}

int main(void)
{
	scanf("%d", &N); 

	int min_height = 0x7FFFFFFF;
	int max_height = -1;

	for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
		scanf("%d", height[i] + j);
		if(max_height < height[i][j]) {
			max_height = height[i][j];
		}
		if(min_height > height[i][j]) {
			min_height = height[i][j];
		}
	}

	int max_group_idx = 0;

	for(int h=min_height; h<=max_height; ++h) {

		for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
			group[i][j] = -1;
		}
		group_idx = 0;

		for(int i=0; i<N; ++i) for(int j=0; j<N; ++j) {
			if(try_group(i, j, h, group_idx)) {
				group_idx++;
			}
		}

		// printf("------h: %d ---------\n", h);
		// for(int i=0; i<N; ++i) {
		// 	for(int j=0; j<N; ++j) {
		// 		printf("%2d ", group[i][j]);
		// 	} printf("\n");
		// }

		if(max_group_idx < group_idx) {
			max_group_idx = group_idx;
		}
	}

	printf("%d", max_group_idx);

	return 0;
}