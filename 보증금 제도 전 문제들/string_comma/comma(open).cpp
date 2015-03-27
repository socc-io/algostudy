#include <stdio.h>
#include <string.h>
int main(){
	char arr[101];
	int flag =0;
	int tmp;
	scanf("%s",&arr);
	tmp = strlen(arr)%3;
	if(strlen(arr) <= 3){
		printf("%s",arr);
	}
	else{
		if(tmp != 0){
			for(int i=0;i<tmp;i++){
				printf("%c",arr[i]);
			}
			printf(",");
		}
		
		for(int i=tmp;i<strlen(arr);i++){
			printf("%c",arr[i]);
			if((i-tmp)%3 == 2 && i!=strlen(arr)-1)
				printf(",");
		}
	}
	return 0;
}