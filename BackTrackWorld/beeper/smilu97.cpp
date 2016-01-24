#include <stdio.h>
int map_x, map_y;
int char_x, char_y;
int npos;
int *pos_x;
int *pos_y;
int **distance;
bool *isVisited;
int best = 999999;

void ref(int me=0, int sum=0)
{
	isVisited[me] = true;
	bool check = true;
	for(int i=0;i<npos; ++i)
	{
		if(!(isVisited[i])){
			ref(i, sum+distance[me][i]);
			check=false;
		}
	}
	if(check)
	{
		int result = sum + distance[0][me];
		if(result < best) best = result;
	}
	isVisited[me] = false;
}

int main(void)
{
	scanf("%d%d", &map_x, &map_y); // map size
	scanf("%d%d", &char_x, &char_y); // position of character
	scanf("%d", &npos); // the number of devices
	pos_x = new int[npos+1];
	pos_y = new int[npos+1];
	isVisited = new bool[npos+1];
	for(int i=0;i<=npos; ++i)
	{
		isVisited[i] = false;
	}
	pos_x[0] = char_x; // position index 0 is character
	pos_y[0] = char_y;
	for(int i=1; i <= npos; ++i)
	{
		scanf("%d%d", &pos_x[i], &pos_y[i]);
	}
	++npos;
	distance = new int*[npos];
	for(int i=0;i<npos; ++i)
	{
		distance[i] = new int[npos];
	}
	for(int i=0;i<npos; ++i)
	{
		for(int j=i; j<npos; ++j)
		{
			int deltax = pos_x[i] - pos_x[j];
			int deltay = pos_y[i] - pos_y[j];
			if(deltax < 0) deltax *= -1;
			if(deltay < 0) deltay *= -1;
			distance[i][j] = deltax+deltay;
			distance[j][i] = distance[i][j];
		}
	}
	ref(0,0);
	printf("%d",best);
	/////
	delete[] pos_x;
	delete[] pos_y;
	for(int i=0;i<npos; ++i)
	{
		delete[] distance[i];
	}
	delete[] distance;
}