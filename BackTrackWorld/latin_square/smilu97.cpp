#include <stdio.h>
#pragma warning(disable:4996)

int **col;
int **rows;
int rows_num;
int rows_index = 0;
int n;
int *factorials;
int Count = 0;

inline void Setfactorial() {
	factorials[0] = 1;
	factorials[1] = 1;
	for (int i = 2; i <= n; ++i) {
		factorials[i] = factorials[i - 1] * i;
	}
}

void GetAnswer(int x, int starting)
{
	if (x == n - 1) {
		++Count;
		return;
	}
	int nextx = x + 1;
	int cur = 0;
	while (cur < rows_index) {
		bool check = true;
		for (int i = 0; i < n; ++i) {
			if (col[i][rows[cur][i]]) {
				cur += factorials[n - i - 1];
				check = false;
				break;
			}
		}
		if (check) {
			if (starting < cur) {
				int* nowrow = rows[cur];
				for (int i = 0; i < n; ++i) {
					col[i][nowrow[i]] = 1;
				}
				GetAnswer(nextx, cur);
				for (int i = 0; i < n; ++i) {
					col[i][nowrow[i]] = 0;
				}
			}
			++cur;
		}
	}
}

void SetRows(int it = 0)
{
	if (it == n) {
		int* nextrow = rows[rows_index + 1];
		int* nowrow = rows[rows_index];
		for (int i = 0; i < n; ++i) {
			nextrow[i] = nowrow[i];
		}
		++rows_index;
	}
	for (int i = 0; i < n; ++i) {
		bool check = true;
		for (int j = 0; j < it; ++j) {
			if (rows[rows_index][j] == i) {
				check = false;
				break;
			}
		}
		if (check) {
			rows[rows_index][it] = i;
			SetRows(it + 1);
		}
	}
}

int main(void) {
	scanf("%d", &n);
	col = new int*[n];
	for (int i = 0; i < n; ++i) {
		col[i] = new int[n];
	}
	factorials = new int[n + 1];
	Setfactorial();
	//printf("Setted Factorials!\n");
	rows_num = factorials[n];
	rows = new int*[rows_num+1];
	for (int i = 0; i <= rows_num; ++i) {
		rows[i] = new int[n];
	}
	SetRows();
	//printf("Setted Rows!\n");
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j) col[i][j] = 0;
	for (int i = 0; i < n; ++i) {
		col[i][i] = 1;
	}
	GetAnswer(1, 0);
	Count = Count * factorials[n - 2];
	//printf("Count : %d\n", Count);
	printf("%d\n", Count);
	delete[] factorials;
	for (int i = 0; i < n; ++i) {
		delete[] rows[i];
	}
	delete[] rows;
	for (int i = 0; i < n; ++i) {
		delete[] col[i];
	}
	delete[] col;
}