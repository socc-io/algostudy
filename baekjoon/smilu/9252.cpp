#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> pos;

char a[1000], b[1000];
int lcs[1001][1001];
pos trk[1001][1001];
char lcss[1001];

int a_len, b_len;

void LCS()
{
	for(int i=0; i<a_len; ++i) {
		lcs[i][0] = 0;
	}
	for(int i=0; i<b_len; ++i) {
		lcs[0][i] = 0;
	}
	for(int i=1; i<=a_len; ++i) {
		for(int j=1; j<=b_len; ++j) {
			if(a[i-1] == b[j-1]) {
				lcs[i][j] = lcs[i-1][j-1] + 1;
				trk[i][j] = make_pair(i-1, j-1);
			}
			else {
				if(lcs[i-1][j] > lcs[i][j-1]) {
					lcs[i][j] = lcs[i-1][j];
					trk[i][j] = make_pair(i-1, j);
				}
				else {
					lcs[i][j] = lcs[i][j-1];
					trk[i][j] = make_pair(i, j-1);
				}
			}
		}
	}

	lcss[lcs[a_len][b_len]] = '\0';
	pos cur = make_pair(a_len, b_len);
	while(cur.first != 0 && cur.second != 0) {
		// printf("cur: (%d, %d)\n", cur.first, cur.second);
		pos prev = trk[cur.first][cur.second];
		int cur_lcs = lcs[cur.first][cur.second];
		int prev_lcs = lcs[prev.first][prev.second];
		if(cur_lcs != prev_lcs) {
			lcss[cur_lcs-1] = a[cur.first-1];
		}
		cur = prev;
	}
}

int main(void)
{
	scanf("%s%s", a, b);
	a_len = strlen(a);
	b_len = strlen(b);
	LCS();
	printf("%d\n%s\n", lcs[a_len][b_len], lcss);

	// printf("      ");
	// for(int i=0; i<b_len; ++i) {
	// 	printf("%2c ", b[i]);
	// } printf("\n");
	// for(int i=0; i<=a_len; ++i) {
	// 	printf("%2c ", i==0 ? ' ' : a[i-1]);
	// 	for(int j=0; j<=b_len; ++j) {
	// 		printf("%2d ", lcs[i][j]);
	// 	}
	// 	printf("\n");
	// }
}