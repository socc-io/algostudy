#include <stdio.h>
#include <string.h>

#define ARR_SIZE 10000

int main(int argc, char** argv)
{
	int arr[ARR_SIZE];
	int arr_start = 0;
	int arr_end = 0;
	int command_num;
	int command_idx;
	char command_buffer[100];
	int parameter;
	int i, j;

	scanf("%d", &command_num);
	for(command_idx=0; command_idx<command_num; ++command_idx) {
		scanf("%s", command_buffer);
		if(strcmp(command_buffer, "push") == 0) {
			scanf("%d", &parameter);
			arr[arr_end++] = parameter;
		}
		else if(strcmp(command_buffer, "pop") == 0) {
			if(arr_start < arr_end) printf("%d\n", arr[arr_start++]);
			else printf("-1\n");
		}
		else if(strcmp(command_buffer, "size") == 0) {
			printf("%d\n", arr_end - arr_start);
		}
		else if(strcmp(command_buffer, "empty") == 0) {
			printf("%d\n", arr_start < arr_end ? 0 : 1);
		}
		else if(strcmp(command_buffer, "front") == 0) {
			if(arr_start < arr_end) printf("%d\n", arr[arr_start]);
			else printf("-1\n");
		}
		else if(strcmp(command_buffer, "back") == 0) {
			if(arr_start < arr_end) printf("%d\n", arr[arr_end-1]);
			else printf("-1\n");
		}
	}
}