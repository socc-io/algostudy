#include <cstdio>
#include <cstring>

int N, M;
int doj_num;
int doj_height[500];
int doj_width[500];
char doj_pixel[500][500][500];
int print_num;

char paper[1000][1000];

int main(void)
{
	scanf("%d%d%d", &N, &M, &doj_num);
	for(int i=0; i<doj_num; ++i) {
		scanf("%d%d", doj_height + i, doj_width + i);
		for(int j=0; j<doj_height[i]; ++j) {
			scanf("%s", doj_pixel[i][j]);
		}
	}
	scanf("%d", &print_num);

	memset(paper, '.', sizeof(paper));
	for(int i=0; i<print_num; ++i) {
		int type, sx, sy;
		scanf("%d%d%d", &type, &sx, &sy);
		type--;
		int h = doj_height[type];
		int w = doj_width[type];
		for(int j=0; j<h; ++j) {
			memcpy(paper[sx + j] + sy, doj_pixel[type][j], w);
		}
	}
	for(int i=0; i<N; ++i) {
		paper[i][M] = '\0';
		printf("%s\n", paper[i]);
	}
}