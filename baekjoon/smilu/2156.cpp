#include <cstdio>
#include <cstdlib>

int n;
int amount[10010];
int dpAmount[10010][4];
int maxAmount;

int max2(int a, int b) {
	return a > b ? a : b;
}
int max3(int a, int b, int c) {
	return max2(a, max2(b, c));
}

int M(int idx, int R)
{
	if (idx < 0) return 0;
	if(dpAmount[idx][R] != -1) return dpAmount[idx][R];
	if (R == 0) {
		dpAmount[idx][0] = max3(M(idx-1, 0), M(idx-1, 1), M(idx-1, 2));
	}
	else if (R == 1) {
		dpAmount[idx][1] = M(idx-1, 0) + amount[idx];
	}
	else if (R == 2) {
		dpAmount[idx][2] = M(idx-1, 1) + amount[idx];
	}
	maxAmount = max2(maxAmount, dpAmount[idx][R]);
	return dpAmount[idx][R];
}

int main(void)
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d", amount+i);
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<4; ++j) {
			dpAmount[i][j] = -1;
		}
	}
	maxAmount = -99999;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<3; ++j) {
			M(i, j);
		}
	}
	printf("%d\n", maxAmount);
}