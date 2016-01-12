#include <stdio.h> 
#include <math.h>
int *gem = 0;
int gem_sum = 0;
int gem_sumd = 0;
int n = 0;
int count = 0;
int cal_count = 0;
bool run = true;
int npowd = 0;
void ref(int it = 0, int val = 0)
{
	if (run)
	{
		if (it == n)
		{
			++cal_count;
			if (val == gem_sumd)
			{
				count += 2;
			}
			if (cal_count == npowd) run = false;
		}
		else
		{
			ref(it + 1, val);
			ref(it + 1, val + gem[it]);
		}
	}	 			   	
}
int main(void)
{
	scanf_s("%d", &n);
	npowd = pow(2.0f, n-1);
	gem = new int[n];
	for (int i = 0; i < n; ++i)
	{
		scanf_s("%d", &gem[i]);
	}
	for (int i = 0; i < n; ++i)
	{
		gem_sum += gem[i];
	}
	if (gem_sum % 2 == 1) printf("Impossible\n");
	else
	{
		gem_sumd = gem_sum / 2;
		ref();
		if (count == 0) printf("Impossible\n");
		else printf("%d\n", count);
	}
	delete[] gem;
}
