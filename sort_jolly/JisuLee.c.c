#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, int n);

int main(){
	int nNum,
		i, j,
		*arr, *result,
		n;

	scanf("%d", &nNum);
	arr = (int *)malloc(nNum * sizeof(int));
	result = (int *)malloc(nNum * sizeof(int));

	for (i = 0; i < nNum; i++){
		scanf("%d", &arr[i]);
	}

	bubble_sort(arr, nNum);

	if (nNum % 2 == 0)	n = nNum / 2;
	else				n = nNum / 2 + 1;

	for (i = 0; i < n; i++){
		result[2*i] = arr[i];
		if (2 * i + 1 < nNum){
			result[2 * i + 1] = arr[n + i];
		}
	}

	for (j = 0; j < nNum; j++){
		printf("%d ", result[j]);
	}

}

void bubble_sort(int *arr, int n){
	int i, j,
		temp;

	for (i = n-1; i > 0; i--){
		for (j = 0; j < i; j++){
			if (arr[j] > arr[j + 1]){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}