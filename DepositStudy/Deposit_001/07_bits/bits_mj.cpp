#include <stdio.h>

int main(){
	int n,m;
	int fir;
	int i,j;
	unsigned long long int up;
	unsigned long long int down;
	int flag;
	unsigned long long int sum=0;
	scanf("%d %d",&n,&m);
	for(i=m;i>0;i--){
		if(i>n/2)
			fir = i;
		else
			fir = n-i;
		up = 1;
		down = 1;
		flag = 1;
		for(j=n;j>fir;j--){
			//printf("드러오기전-- %d %d %lld %lld\n",j, flag,up, fir);
			up *= j;
			down *= flag;
			flag++;
		}
		//printf("-- %lld %lld %lld\n",up,down,up/down);
		sum += (up/down);
	}
	printf("%lld",sum+1);
	return 0;
}