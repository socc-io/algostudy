#include<stdio.h>

void bong(int n){
	if(n == 1) printf("%d",n);

	if(n>1){ bong(n-1);printf("%d",n);bong(n-1); }
}

int main(){	
	int input;
	scanf("%d",&input);

	bong(input);


}
