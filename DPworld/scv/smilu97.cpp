#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > map;
vector<vector<int> > maxvalue;
int n;

int getmax(int a, int b)
{
	if(a>b){
		return a;
	}
	else return b;
}

int main(void)
{
	cin >> n;
	map.resize(n);
	maxvalue.resize(n);
	for(int i=0;i<n;++i){
		map[i].resize(n, 0);
		maxvalue[i].resize(n, 0);
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			cin >> map[i][j];
		}
	}
	for(int i=0;i<n;++i){
		maxvalue[i][0] = map[i][0];
		maxvalue[0][i] = map[0][i];
	}
	for(int x=1; x<n;++x){
		for(int y=1;y<n;++y){
			maxvalue[x][y] = getmax(maxvalue[x-1][y], maxvalue[x][y-1]) + map[x][y];
		}
	}
	cout << maxvalue[x-1][y-1] << endl;
	return 0;
}