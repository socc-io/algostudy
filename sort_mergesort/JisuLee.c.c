#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *sort(int *arr1, int *arr2, int size1, int size2){
	int i = 0, j = 0, k=0, t,
		*arrResult;
	int size = size1 + size2;

	arrResult = (int *)malloc(size * sizeof(int));

	while (k < size){
		while (arr1[i] <= arr2[j] && k < size && i < size1){
			arrResult[k] = arr1[i];
			i++; k++;
		}
		if (i >= size1){
			for (t = k; t<size; t++){
				arrResult[t] = arr2[j];
				j++;
			}
			return arrResult;
		}
		while (arr1[i] > arr2[j] && k < size && j < size2){
			arrResult[k] = arr2[j];
			j++; k++;
		}
		if (j >= size2){
			for (t = k; t<size; t++){
				arrResult[t] = arr1[i];
				i++;
			}
			return arrResult;
		}
	}
 } 

int* merge_sort(int arr[10], int start, int end){
	int *tempResult, *temp_1, *temp_2,
		size1 = (end + start) / 2 - start + 1,
		size2 = end - (end + start) / 2;

	if (start == end){
		tempResult = (int *)malloc(sizeof(int));
		tempResult[0] = arr[start];
		
	}
	else{
		temp_1 = merge_sort(arr, start, (start + end) / 2);
		temp_2 = merge_sort(arr, (start + end) / 2 + 1, end);

		//printf("arr_size : %d\n", arr_size);
		tempResult = sort(temp_1, temp_2, size1, size2);
	}
	//for (int i = 0; i < size1 + size2; i++){
	//	printf("%d ", tempResult[i]);
	//}
	//puts("");
	//p++;
	return tempResult;
}

int main(){
	int i = 0, j,
		arr[10] = { 4, 1, 2, 3, 4, 5, 1, 2, 1, 3 }, *result;

	result = (int *)malloc(10 * sizeof(int));
	result = merge_sort(arr, 0, 9);

	for (i = 0; i < 10; i++){
		printf("%d ", result[i]);
	}
	puts("");
	
	return 0;
}