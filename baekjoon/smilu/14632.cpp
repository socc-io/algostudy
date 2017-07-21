#include <cstdio>
#include <cstring>

int N, M;
int doj_num;
int doj_height[500];
int doj_width[500];
char doj_pixel[500][500][500];
int print_num;
int print_type[10000];
int print_x[10000];
int print_y[10000];

char paper[1000][1000];
int paper_next[1000][1000];

int printed[1000];
int printed_num=0;

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
	memset(paper_next, -1, sizeof(paper_next));
	for(int i=0; i<print_num; ++i) {
		scanf("%d%d%d", print_type+i, print_x+i, print_y+i);
		print_type[i]--;
	}
	for(int print_idx=print_num-1; print_idx >= 0; --print_idx) {

		int type = print_type[print_idx];
		int h = doj_height[type];
		int w = doj_width[type];
		int sx = print_x[print_idx];
		int sy = print_y[print_idx];
		char* pixel = (char*)doj_pixel[type];
		int dx, dy, px, py, pdy;

		for(dx=0; dx<h; ++dx) {
			px = sx + dx;
			printed_num = 0;
			for(dy=0; dy<w;) {
				py = sy + dy;
				if(paper_next[px][py] == -1) {
					paper[px][py] = pixel[dx * 500 + dy];
					printed[printed_num++] = py;
					++dy;
				} else{
					dy = paper_next[px][py] - sy;
				}
			}
			pdy = sy + dy;
			while(pdy < M && paper_next[px][pdy] != -1) {
				pdy = paper_next[px][pdy];
			}
			for(int i=0; i<printed_num; ++i) {
				paper_next[px][printed[i]] = pdy;
			}
		}
	}
	for(int i=0; i<N; ++i) {
		paper[i][M] = '\0';
		printf("%s\n", paper[i]);
	}
}