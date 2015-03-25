#include <stdio.h>

int main(){
	int num;
	int i = 1;
	int arr[101];
	int stack[102];
	int addr_stack=-1;
	int compare = 1;
	scanf("%d",&num);
	for(int i=1;i<=num;i++)
		scanf("%d",&arr[i]);
	while(true){
		if(addr_stack == -1 && i!=num+1){
			addr_stack++;
			stack[addr_stack] = i;
			i++;
			///printf("flag1\n");
		}
		else if(stack[addr_stack] < arr[compare]){
			addr_stack++;
			stack[addr_stack] = i;
			i++;
			//printf("flag2\n");
		}
		else if(stack[addr_stack] == arr[compare]){
			addr_stack--;
			compare++;
			//printf("flag3\n");
			//printf("i = %d\n",i);
			//printf("addr_stack = %d\n",addr_stack);
			//printf("stack = %d\n",stack[addr_stack]);
			//printf("compare : %d, arr[%d] : %d\n",compare,compare,arr[compare]);
			if(addr_stack == -1 && i==num+1){
				printf("YES");
				return 0;
			}
		}
		//else if(addr_stack == -1 && i==num+1){
		//	printf("YES");
		//	return 0;
		//}
		else{
			printf("NO");
			return 0;
		}


	}
	return 0;
}