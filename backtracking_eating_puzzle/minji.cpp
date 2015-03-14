#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int main(){
	int basket[23];
	int C;
	int B;
	int bi[20];
	int num_2=1;
	int addr;
	int max = 0;
	int sum = 0;
	int temp;
	scanf("%d",&C);
	scanf("%d",&B);
	for(int i=0;i<B;i++){
		scanf("%d",&basket[i]);
		num_2 *= 2;
	}
	sort(basket, basket+B);
	for(int j=1;j<num_2;j++){
		temp = j;
		sum = 0;
		for(int h=B;h>0;h--){
			if(h>2){
				bi[h] = temp%2;
				temp = temp/2;
			}
			else if(h==2){
				bi[2] = temp%2;
				bi[1] = temp/2;
			}
		}
		for(int ss = 1;ss<=B;ss++){
			if(bi[ss] == 1)
				sum = sum + basket[ss-1];
		}

		if(sum <= C && sum > max){
			max = sum;
		}		
	}
	printf("%d",max);
	return 0;
}