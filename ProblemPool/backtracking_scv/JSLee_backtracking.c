#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct _scv{
	int row, col;
	int nMineral;
}SCV;

void push(int n);
int pop();

int tmp = 0;
int *arr = NULL;
int index = 0;


int main(){
	int N, i, j, k=0,
		row=0, col=0,
		**map, val;
	SCV now, cand0, cand1;

	scanf("%d", &N);
	
	map = (int **)malloc(sizeof(int *)*N);
	for (i = 0; i < N; i++){
		map[i] = (int *)malloc(N*sizeof(int));
		for (j = 0; j < N; j++){
			scanf("%d", &map[i][j]);
		}
	}
	
	now.row = 0; now.col = 0; now.nMineral = 0;
	cand0.row = 0; cand0.col = 0; cand0.nMineral = 0;
	cand1.row = 0; cand1.col = 0; cand1.nMineral = 0;
	
	push(0 + 100*map[0][0]);

	while (1){
		val = pop();
		if (val == -1){
			printf("%d", tmp);
			return 0;
		}
		now.row = (val % 100) / 10;
		now.col = (val % 100) % 10;
		now.nMineral = val / 100;

		printf("row: %d col: %d M: %d\n", now.row, now.col, now.nMineral);

		if (now.row == N - 1 && now.col == N - 1){
			tmp = (now.nMineral > tmp) ? now.nMineral : tmp;
		}

		cand0.row = now.row; cand0.col = now.col; cand0.nMineral = now.nMineral;
		if (now.row + 1 < N){
			cand0.row++;
			if (map[cand0.row][cand0.col]) cand0.nMineral++;
			push(100 * cand0.nMineral + 10 * cand0.row + cand0.col);
		}
		cand1.row = now.row; cand1.col = now.col; cand1.nMineral = now.nMineral;
		if (now.col + 1 < N){
			cand1.col++;
			if (map[cand1.row][cand1.col]) cand1.nMineral++;
			push(100 * cand1.nMineral + 10 * cand1.row + cand1.col);
		}
	}

}

int pop(){
	if (index == 0){
		return -1;
	}

	index--;
	return arr[index];
}

void push(int n){
	if (index == 0){
		arr = (int *)malloc(sizeof(int));
		arr[0] = n;	index++;
		return;
	}

	arr = (int *)realloc(arr, (index + 1)*sizeof(int));
	arr[index] = n;	index++;
}