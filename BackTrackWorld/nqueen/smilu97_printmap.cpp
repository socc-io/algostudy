#include <stdio.h>

int n = -1;

int map[100][100];
int fill[100][100];
int count = 0;

void addfill(int x, int y, int val)
{
	for(int j=0;j<n; ++j)
	{
		int iy = y-x+j;
		if(0<=iy && iy < n)
		{
			fill[j][iy]+=val;
		}
		iy = y+x-j;
		if(0<=iy && iy < n)
		{
			fill[j][iy]+=val;
		}
		fill[j][y]+=val;
	}
	fill[x][y] -= val*2;
}

void ref(int it)
{
	if(it==n)
	{
		++count;
		if(count <= 3)
		{
			for(int i=0;i<n; ++i)
			{
				for(int j=0;j<n;++j)
				{
					if(map[i][j] == 1)
					{
						printf("%d ", j+1);
					}
				}
			}
			printf("\n");
		}
		return;
	}
	for(int i=0;i<n; ++i) // (it, i)
	{
		if(fill[it][i] == 0)
		{
			map[it][i] = 1;
			addfill(it,i,1);
			ref(it+1);
			addfill(it,i,-1);
			map[it][i] = 0;
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	for(int i=0;i<n; ++i)
	{
		for(int j=0;j<n; ++j)
		{
			map[i][j] = 0;
			fill[i][j] = 0;
		}
	}
	ref(0);
	printf("%d",count);
	return 0;
}