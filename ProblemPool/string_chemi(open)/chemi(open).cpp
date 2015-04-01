#include <stdio.h>
#include <string.h>
int main(){
	// (a,e,i,o,u)
	int i,j;
	int flag = 0;
	char arr[101];
	char answer[101];
	gets(arr);
	for(i=0;i<strlen(arr);i++){
		if(arr[i] == 'p'){
			if(arr[i-1] == 'a' && arr[i+1] == 'a'){
				arr[i] = '/';
				arr[i+1] = '/';
			}
			else if(arr[i-1] == 'e' && arr[i+1] == 'e'){
				arr[i] = '/';
				arr[i+1] = '/';
			}
			else if(arr[i-1] == 'i' && arr[i+1] == 'i'){
				arr[i] = '/';
				arr[i+1] = '/';
			}
			else if(arr[i-1] == 'o' && arr[i+1] == 'o'){
				arr[i] = '/';
				arr[i+1] = '/';
			}
			else if(arr[i-1] == 'u' && arr[i+1] == 'u'){
				arr[i] = '/';
				arr[i+1] = '/';
			}
		}

	}
	
	for(i=0;i<strlen(arr);i++){
		if(arr[i] != '/'){
			printf("%c",arr[i]);
		}
	}
	return 0;
}