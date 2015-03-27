#include <stdio.h>

int main(){
	int num;
	int odd[1001];
	int sum = 0;
	int i,j;
	scanf("%d",&num);
	for(i=0;i<num;i++){
		odd[i] = (2*i)+1;
	}
	for(i=0,j=num-1;i<num,j>=0;i++,j--){
		sum += odd[i] * odd[j];
	}
	printf("%d",sum);
	return 0;
}