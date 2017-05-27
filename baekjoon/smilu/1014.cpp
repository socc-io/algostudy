#include <cstdio>
#include <cstdlib>

FILE *fp;
char tile[11][11];
int N, M;

int leftRight[100];
int rightLeft[100];
int conn[100][100];
int idxmap[100][100];

int leftNum, rightNum;

bool tryConnect(int left)
{
	if(leftRight[left] != -1) return false;
	for(int right=0; right<rightNum; ++right) {
		if(conn[left][right] == 0) continue;
		if(rightLeft[right] == -2) continue;
		if(rightLeft[right] == -1) {
			leftRight[left] = right;
			rightLeft[right] = left;
			return true;
		}
		else {
			int oleft = rightLeft[right];
			leftRight[oleft] = -1;
			rightLeft[right] = -2;
			if(tryConnect(oleft)) {
				leftRight[left] = right;
				rightLeft[right]= left;
				return true;
			}
			else {
				leftRight[oleft] = right;
				rightLeft[right] = oleft;
			}
		}
	}
	return false;
}

void build(int x1, int y1, int x2, int y2) {
	if(y1 < 0 || M <= y1 || y2 < 0 || M <= y2) return;
	if(tile[x2][y2] != '.') return;
	int left = idxmap[x2][y2];
	int right = idxmap[x1][y1];
	conn[left][right] = 1;
}

void run()
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) {
		scanf("%s", tile[i]);
	}
	int dotnum = 0;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			if(tile[i][j] == '.') ++dotnum;
		}
	}
	int k=0;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; j+=2) {
			idxmap[i][j] = k++;
		}
	}
	leftNum = k;
	k=0;
	for(int i=0; i<N; ++i) {
		for(int j=1; j<M; j+=2) {
			idxmap[i][j] = k++;
		}
	}
	rightNum = k;
	for(int i=0; i<100; ++i) {
		for(int j=0; j<100; ++j) {
			conn[i][j] = 0;
		}
		leftRight[i] = -1;
		rightLeft[i] = -1;
	}
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			if(tile[i][j] != '.') continue;
			build(i, j, i-1, j-1);
			build(i, j, i,   j-1);
			build(i, j, i-1, j+1);
			build(i, j, i,   j+1);
		}
	}
	int cnt = 0;
	while(true) {
		bool flag = true;
		for(int i=0; i<leftNum; ++i) {
			if(tryConnect(i)) {
				flag = false;
				++cnt;
			}
		}
		if(flag) break;
	}
	for(int left=0; left<leftNum; ++left) {
		if(leftRight[left] != -1) {
			
		}
	}
	printf("%d\n", dotnum-cnt);
}

int main(void)
{
	int T;
	// fp = fopen("input.txt", "r");
	scanf("%d", &T);
	for(int i=0; i<T; ++i){
		run();
	}
	// fclose(fp);
	return 0;
}