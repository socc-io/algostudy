#include <stdio.h>

int main(int argc, char** argv)
{
	int *arr;
	int left, right;
	scanf("%d %d", &left, &right);
	if(left < 1) left = 1;
	int size = right-left+1;
	arr = new int[size];
	for(int i=0;i<size;++i) arr[i] = 0;
	int right_h = right / 2;

	if(left == 1) {
		arr[0] = 1;
	}
	else if(left == 0) {
		arr[0] = 1;
		arr[1] = 1;
	}

	for(int filter_base=2;filter_base<=right_h;++filter_base) {
		bool inrange = left <= filter_base;
		if(inrange) {
			if(arr[filter_base-left] == 1) continue;
		}

		int start = filter_base - (left % filter_base);
		start = start == filter_base ? 0 : start;
		start += left;
		if(start <= filter_base) start = filter_base << 1;
		for(int filter_cursor = start; filter_cursor <= right; filter_cursor += filter_base) {
			arr[filter_cursor-left] = 1;
		}
	}

	for(int i=0;i<size;++i) {
		if(arr[i] == 0) {
			printf("%d\n", i+left);
		}
	}

	delete[] arr;
	return 0;
}