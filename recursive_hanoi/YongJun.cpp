#include<stdio.h>

void hanoi(int n,int start,int tmp,int end)
{
	if(n>0){
		hanoi(n-1,1,tmp,3);
		if(n % 2 == 0) printf("%d->%d\n",start,tmp);
		else printf("%d->%d\n",tmp,end);
		hanoi(n-1,1,tmp,3);
	}
}

int main()
{
	int input;
	scanf("%d",&input);

	hanoi(input,1,2,3);
}