#include <stdio.h>
#include <string.h>

int main(){
	char arr[52];
	int left=0, right=0;
	int L[52];
	scanf("%s",&arr);
	for(int i=0;i<strlen(arr);i++){
		if(arr[i] == '('){
			left++;
		}
		else if(arr[i] == ')'){
			right++;
			if(left < right){
				printf("not match");
				return 0;
			}
		}
	}
	if(left != right){
		printf("not match");
		return 0;
	}
	left = 0;
	for(int i=0;i<strlen(arr);i++){
		if(arr[i] == '('){
			L[left] = i;
			left++;
		}
		else if(arr[i] == ')'){
			printf("%d %d\n",L[left-1],i);
			left--;
		}
	}
	return 0;
}