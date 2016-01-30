#include <stdio.h>

// 너무 느려서 타임오버

#pragma warning(disable:4996)

int arr[200];
int index_arr = 0;
int dest = -1;

int best_arr[200];
int best_arr_size = -1;

void ref()
{
	int last = arr[index_arr - 1];
	for (int i = 0; i < index_arr;++i)
	{
		int added = last + arr[i];
		if (added < dest) {
			arr[index_arr++] = added;
			ref();
			--index_arr;
		}
		else if (added == dest) {
			arr[index_arr++] = added;
			if (best_arr_size == -1 || index_arr < best_arr_size) {
				best_arr_size = index_arr;
				for (int j = 0; j < index_arr; ++j) {
					best_arr[j] = arr[j];
				}
			}
			--index_arr;
		}
	}
}

int main(void) {
	scanf("%d", &dest);
	arr[0] = 1;
	index_arr = 1;
	ref();
	for (int i = 0; i < best_arr_size; ++i) {
		printf("%d ", best_arr[i]);
	}
	printf("\n");
	return 0;
}