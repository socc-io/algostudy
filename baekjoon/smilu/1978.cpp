#include <stdio.h>

bool isPrime(int num)
{
	if(num<=1) return false;
	int numd = num / 2;
	for(int i=2;i<=numd;++i) {
		if(num%i == 0) return false;
	}
	return true;
}

int main(int argc, char** argv)
{
	int N;
	int *num;
	scanf("%d", &N);
	num = new int[N];
	int primeCnt = 0;
	for(int i=0;i<N;++i) {
		scanf("%d", &num[i]);
		if(isPrime(num[i])) primeCnt++;
	}
	printf("%d\n",primeCnt);


	delete[] num;

	return 0;
}