#include <stdio.h>
int arr[1000001];
int main(){
	int num1,num2;
	int start=0,end=0;
	int sum;
	scanf("%d",&num1);
	for(int i=0;i<num1;i++){
		scanf("%d",&arr[i]);
	}
	scanf("%d",&num2);
	for(int i=0;i<num2;i++){
		scanf("%d %d",&start,&end);
		sum = 0;
		for(int j=start-1;j<end;j++){
			sum += arr[j];
		}
		printf("%d\n",sum);
	}
	return 0;
}