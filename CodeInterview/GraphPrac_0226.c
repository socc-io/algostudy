#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct stack{
	int s[10000];
	int index;
}stack;

int pop(stack* stk){
	if(stk->index<0){
		printf("스택이 비어있습니다.");
		return 0;
	}else{
		return stk->s[stk->index--];
	}
}
int push(stack* stk,int key){
	if(stk->index>=10000){
		printf("스택이 가득 차 있습니다.");
		return 0;
	}else{
		stk->index++;
		stk->s[stk->index] = key;
		return 1;
	}
}
int peek(stack* stk){
	return stk->s[stk->index];
}

int randInit(int size, int** matrix){
	for(int i = 0; i<size; i++){
		for(int j = 0; j<size;j++){
			if(rand()%10>5){
				matrix[i][j] = 1;
			}
			else {
				matrix[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int findRoute(int size, int**matrix,int start, int end){
	int** check = (int**)malloc(size*sizeof(int**));
	for(int i = 0; i<size; i++){
		check[i] = (int*)malloc(size*sizeof(int*));	
	}
	stack stk;
	stk.index = -1;

	push(&stk, start);

	int i;
	while (stk.index >= 0) {
		for(i = 0; i<size;i++){
			if (matrix[stk.s[stk.index]][i] == 1) {
				if (i == end) {
					return 1;
				}
				else if (check[stk.s[stk.index]][i] != 1) {
					check[stk.s[stk.index]][i] = 1;
					push(&stk, i);
					break;
				}
			}
		}
		if(i == size)pop(&stk);
	}
	return 0;
}

int main(){
	int size;
	int start;
	int end;
	scanf("%d %d %d",&size,&start,&end);
	int**matrix = (int**)malloc(size*sizeof(int*));
	for(int i = 0; i<size;i++){
		matrix[i] = (int*)malloc(size*sizeof(int));
	}
	randInit(size,matrix);
	if (findRoute(size, matrix, start, end) == 1) {
		printf("경로가 있습니다.");
	}
	else {
		printf("경로가 없습니다.");
	}

}
