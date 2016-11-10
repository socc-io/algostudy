#include <stdio.h>

int main(void)
{
	int N;
	int *arr;
	scanf("%d", &N);
	arr = new int[N];
	int *stack = new int[N+1];
	int *res = new int[3*N];
	int stack_size = 0;
	int res_size = 0;
	int last_push = 0;
	for(int i=0;i<N;++i) scanf("%d", &arr[i]);
	for(int i=0;i<N;++i) {
		if(arr[i] == stack[stack_size-1]) {
			stack_size--;
			res[res_size++] = -1;
			continue;
		}
		if(last_push <= arr[i]) {
			int push_num = arr[i] - last_push;
			for(int j=0;j<push_num;++j) {
				res[res_size++] = 1;
				stack[stack_size++] = ++last_push;
			}
			i--;
			continue;
		}
		res_size = -1;
		break;
	}
	if(res_size != -1) {
		for(int i=0;i<res_size;++i) {
			if(res[i] == 1) {
				printf("+\n");
			}
			else if(res[i] == -1) {
				printf("-\n");
			}
		}
	}
	else {
		printf("NO");
	}

	delete[] arr;
	delete[] stack;
	delete[] res;
	return 0;
}