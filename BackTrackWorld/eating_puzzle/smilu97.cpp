#include <stdio.h> 
int *bList = 0;
int  n = 0;
int maxc = 0;
int bestc = 0;
void reSolver(int iterator = 0, int fc = 0)
{
	if (fc > maxc)
	{
		int nc = fc - bList[iterator - 1];
		if (nc > bestc) bestc = nc;
	}
	else if (iterator == n)
	{
		int nc = fc;
		if (nc > bestc) bestc = nc;
	}
	else
	{
		reSolver(iterator + 1, fc);
		reSolver(iterator + 1, fc + bList[iterator]);
	}								 	
}
int main(void)
{
	scanf_s("%d %d", &maxc, &n);
	bList = new int[n];
	for (int i = 0; i < n; ++i) scanf_s("%d", &bList[i]);
	reSolver();
	printf("%d", bestc);
}
