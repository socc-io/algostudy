#include <stdio.h>
int fact[10] = {0, };

int sub(int num){
	fact[0] = 1;
	int sum = 0;
	int temp;
	do{
		sum += fact[num%10]; 
	}while((num/=10) > 10);
	sum += fact[num%10];
	return sum;
}
int main(){
	//두 자리수 이상 1000000 이하인
	for(int i=1;i<=9;i++){
		fact[i] = 1;
	}
	for(int i=1;i<10;i++){
		for(int j=1;j<=i;j++){
			fact[i] *= j;
		}
	}
	for(int i=10;i<=1000000;i++){
		if(sub(i) == i){
			printf("%d\n",i);
		}
	}

	return 0;
}