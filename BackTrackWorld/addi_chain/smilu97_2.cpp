#include <stdio.h>

// 60정도 이상 부터 결과가 이상함

#pragma warning(disable:4996)

#define MEMSIZE 10000 // 1.5GB

int arr[201][MEMSIZE][200];
int len[201];
int num[201];
int dest = -1;
bool stopexp = false;

int combineArr(int *to, int *a, int size_a, int *b, int size_b)
{
	int count = 0;
	int i_a = 0;
	int i_b = 0;
	int num_a = a[i_a];
	int num_b = b[i_b];
	while (i_a < size_a || i_b < size_b) {
		if (num_a < num_b) {
			to[count++] = num_a;
			num_a = a[++i_a];
			if (i_a == size_a) num_a = 99999;
		}
		else if (num_a > num_b) {
			to[count++] = num_b;
			num_b = b[++i_b];
			if (i_b == size_b) num_b = 99999;
		}
		else {
			to[count++] = num_a;
			num_a = a[++i_a];
			num_b = b[++i_b];
			if (i_a == size_a) num_a = 99999;
			if (i_b == size_b) num_b = 99999;
		}
	}
	return count;
}

void copyArr(int *from, int *to, int size) {
	for (int i = 0; i < size; ++i) {
		to[i] = from[i];
	}
}

void getchains(int n)
{
	bool stop = false;
	int tmp[200];
	int tmp_size = 0;
	int endi = (int)(n / 2) + (n & 1);
	for (int i = 1; i <= endi; ++i) {
		int o = n - i;
		for (int j = 0; j < num[i]; ++j) {
			for (int k = 0; k < num[o]; ++k) {
				tmp_size = combineArr(tmp, arr[i][j], len[i], arr[o][k], len[o]);
				tmp[tmp_size++] = n;
				if (tmp_size < len[n] || len[n] == -1) {
					num[n] = 1;
					len[n] = tmp_size;
					copyArr(tmp, arr[n][0], tmp_size);
				}
				else if (tmp_size == len[n]) {
					if (num[n] < MEMSIZE) {
						copyArr(tmp, arr[n][num[n]++], tmp_size);
					}
					else { // memory is over
						stop = true;
						stopexp = true;
						break;
					}
				}
			}
			if (stop) break;
		}
		if (stop) break;
	}
}
void init()
{
	for (int i = 0; i <= dest; ++i) {
		len[i] = -1;
	}
	arr[1][0][0] = 1;
	len[1] = 1;
	num[1] = 1;
	arr[2][0][0] = 1;
	arr[2][0][1] = 2;
	len[2] = 2;
	num[2] = 1;
	arr[3][0][0] = 1;
	arr[3][0][1] = 2;
	arr[3][0][2] = 3;
	len[3] = 3;
	num[3] = 1;
}
int main(void)
{
	scanf("%d", &dest);
	init();
	for (int i = 4; i <= dest; ++i) {
		getchains(i);
	}
	for (int i = 0; i < len[dest]; ++i) {
		printf("%d ", arr[dest][0][i]);
	}
	printf("\n%d\n", stopexp);
	return 0;
}