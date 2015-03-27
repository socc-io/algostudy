#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
	int num;
	char arr1[21];
	char arr2[21];
	char output1[10001] = {0,};
	char output2[10001] = {0,};
	char output3[10001] = {0,};
	scanf("%d",&num);
	scanf("%s",&arr1);
	scanf("%s",&arr2);
	strcat(output1,arr1);
	strcat(output2,arr2);
	for(int i=1;i<=num;i++){
		if(i==1)
			printf("%s\n",arr1);
		else if(i==2)
			printf("%s\n",arr2);
		else{
			
			strcpy(output3,strcat(output1,output2));
			strcpy(output1,output2);
			//printf("%s\n",output2);
			printf("%s\n",output3);
			strcpy(output2,output3);
		}

	}
	return 0;
}