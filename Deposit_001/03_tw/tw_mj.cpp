#include <stdio.h>
	int tw[500001]={0, };
	int stack[500001]={0, };
	int addr[500001]={0, };
int main(){
	int num;
	int top=-1;
	int i;
	scanf("%d",&num);
	for(i=0;i<num;i++){
		scanf("%d",&tw[i]);
	}
	printf("0");
	stack[++top] = tw[0];
	addr[top] = 0;
	for(i=1;i<num;i++){
		while(top > -1 && tw[i] >= stack[top]){
			top--;
		}
		if(top == -1){
			printf(" 0");
			stack[++top] = tw[i];
			addr[top] = i;
		}
		else{
			printf(" %d",addr[top]+1);
			stack[++top] = tw[i];
			addr[top] = i;
		}
	}
	return 0;
}