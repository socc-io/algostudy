#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector< vector< int > > map;

int point[3];
int first[5][2];
int maxvalue = -1;

int getmapvalue(int x, int y)
{
	if(x<0 || y<0) {
		return -1;
	}
	if(x>y) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	if(map[x][y] != -1) {
		return map[x][y];
	}
	for(int i=0;i<3;++i) {
		if (getmapvalue(x-point[i],y) == 0) // lose point
		{
			map[x][y]=1;
			return 1; // I will win!
		}
		if (getmapvalue(x, y-point[i]) == 0)
		{
			map[x][y]=1;
			return 1; // I will win!
		}
	}
	map[x][y] = 0;
	return 0;
}

int main(void)
{
	cin >> point[0] >> point[1] >> point[2];
	for(int i=0;i<5;++i) {
		cin >> first[i][0] >> first[i][1];
		if (maxvalue < first[i][0]) {
			maxvalue = first[i][0];
		}
		if (maxvalue < first[i][1]) {
			maxvalue = first[i][1];
		}
	}
	maxvalue += 1;
	map.resize(maxvalue);
	for(int i=0;i<maxvalue;++i){
		map[i].resize(maxvalue,-1);
	}
	map[0][0] = 0;
	for(int i=0;i<5;++i)
	{
		int mv = getmapvalue(first[i][0], first[i][1]);
		if(mv == 0)
		{
			cout << "B" << endl;
		}
		else if(mv == 1)
		{
			cout << "A" << endl;
		}
		else
		{
			cout << "Error" << endl;
		}
	}
} 