#include <stdio.h> 
int n = 0;
int un = 0;
int *ulist = 0;
int bestco = 999999;
void ref(int cur1, int cur2, int it = 0, int co = 0)
{
	if (it == un)
	{
		if (co < bestco) bestco = co;
	}
	else
	{
		int target = ulist[it];
		if (target == cur1 || target == cur2)
		{
			ref(cur1, cur2, it + 1, co);
		}
		else if (target < cur1)
		{
			ref(target, cur2, it + 1, co + cur1 - target);
		}
		else if (cur2 < target)
		{
			ref(cur1, target, it + 1, co + target - cur2);
		}
		else
		{
			ref(target, cur2, it + 1, co + target - cur1);
			ref(cur1, target, it + 1, co + cur2 - target);
		}
	}				  	
}
int main(void)
{
	int cur1, cur2;
	scanf_s("%d", &n);
	scanf_s("%d", &cur1);
	scanf_s("%d", &cur2);
	if (cur1 > cur2)
	{
		int tmp = cur1;
		cur1 = cur2;
		cur2 = tmp;
	}
	scanf_s("%d", &un);
	ulist = new int[un];
	for (int i = 0; i < un; ++i)
	{
		scanf_s("%d", &ulist[i]);
	}
	ref(cur1, cur2, 0, 0);
	printf("%d\n", bestco);
	delete[] ulist;
}
