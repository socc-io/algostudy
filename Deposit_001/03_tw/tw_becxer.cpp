#include <iostream>
#define MAX_N 1000000

using namespace std;

int stack_index[MAX_N];
int stack_height[MAX_N];
int stack_count = 0;
int pop_index = 0;
int pop_height = 0;

void push(int index, int height){
	stack_index[stack_count] = index;
	stack_height[stack_count++] = height;
}

int pop(){
	pop_index = stack_index[stack_count-1];
	pop_height = stack_height[(stack_count--)-1];
}

bool isEmpty(){
	if(stack_count == 0)
		return true;
	else
		return false;
}

int main(void){
	int num ,now;
	cin >> num;
	for(int i = 0 ; i < num ; i++){
		cin >> now;
		while(true){
			if(isEmpty()){
				cout << "0 ";
				push(i,now);
				break;
			}
			pop();
			if(pop_height >= now){
				cout << pop_index+1 << " ";
				push(pop_index,pop_height);
				push(i,now);
				break;
			}
		}
	}
			
	return 0;
}
