#include <stdio.h>
#include <string.h>
int main(){
	int num;
	int count[11] = {0, };
	char arr[1001] = {0, };
	scanf("%s",&arr);
	count[arr[0]-'0']++;
	for(int i=1;i<strlen(arr);i++){
		count[arr[i]-'0']++;
		if(arr[i-1] != arr[i]){
			printf("%d%d",count[arr[i-1]-'0'],arr[i-1]-'0');
			count[arr[i-1]-'0'] = 0;
			if(i==strlen(arr)-1){
				printf("%d%d",count[arr[i]-'0'],arr[i]-'0');
			}
		}
		else if(i==strlen(arr)-1){
			printf("%d%d",count[arr[i]-'0'],arr[i]-'0');
		}
	}
	return 0;
}