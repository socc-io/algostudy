#include <stdio.h>

int map[9][9];
int block[3][3][9];
int ver[9][9];
int hor[9][9];
int blankstack[81];
int blankstack_index = 0;
class pos
{
public :
	int x;
	int y;
	void operator=(pos tmp)
	{
		x = tmp.x;
		y = tmp.y;
	}

};
pos blank[81];
int blank_index = 0;

bool printmap_limit = true;

void printmap()
{
	if(!printmap_limit)
	{
		return;
	}
	printf("\n");
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<9; ++j)
		{
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
	printmap_limit=false;
}

void ref(int it=0)
{
	if(printmap_limit)
	{
		if(it == blank_index)
		{
			for(int i=0;i<blank_index; ++i)
			{
				map[blank[i].x][blank[i].y] = blankstack[i];
			}
			printmap();
			return;
		}
		pos blankpos = blank[it];
		for(int i=0;i<9; ++i)
		{
			if(hor[blankpos.x][i]==0 && ver[blankpos.y][i] == 0 && block[blankpos.x/3][blankpos.y/3][i] == 0)
			{
				blankstack[blankstack_index] = i+1;
				++blankstack_index;
				hor[blankpos.x][i] = 1;
				ver[blankpos.y][i] = 1;
				block[blankpos.x/3][blankpos.y/3][i] = 1;
				ref(it+1);
				hor[blankpos.x][i] = 0;
				ver[blankpos.y][i] = 0;
				block[blankpos.x/3][blankpos.y/3][i] = 0;
				--blankstack_index;
			}
		}	
	}
}

int main(void)
{
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			for(int k=0;k<9;++k)
			{
				block[i][j][k]=0;
			}
		}
	}
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<9;++j)
		{
			ver[i][j] = 0;
			hor[i][j] = 0;
		}
	}
	for(int i=0;i<9;++i)
	{
		char temp_str[10];
		scanf("%s", temp_str);
		for(int j=0; j<9; ++j)
		{
			map[i][j] = temp_str[j]-48;
			if(map[i][j]==0)
			{
				blank[blank_index].x = i;
				blank[blank_index].y = j;
				++blank_index;
			}
			else
			{
				ver[j][map[i][j]-1] = 1;
				hor[i][map[i][j]-1] = 1;
				block[i/3][j/3][map[i][j]-1] = 1;
			}			
		}
	}
	ref(0);
	return 0;
}