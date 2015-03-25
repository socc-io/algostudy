#include <stdio.h>

int main(){
	int num;
	int arr[101];
	int arr_stack[102];
	int addr_stack=-1;
	int compare = 1;
	scanf("%d",&num);
	for(int i=1;i<=num;i++)
		scanf("%d",&arr[i]);
	for(int i=1;i<=num;i++){
		if(addr_stack == -1){
			addr_stack++;
			arr_stack[addr_stack] = i;
			printf("flag1\n");
		}
		else if(arr_stack[addr_stack] < arr[compare]){
			addr_stack++;
			arr_stack[addr_stack] = i;
			printf("flag2\n");
		}
		else if(arr_stack[addr_stack] == arr[compare]){
			addr_stack--;
			compare++;
		}
		else if(addr_stack == 0 && i==num){
			printf("YES");
			return 0;
		}
		else{
			printf("NO");
			return 0;
		}


	}
	return 0;
}