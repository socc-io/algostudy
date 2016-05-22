#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int num;
int start;
vector<vector<int>> edges;
vector<int> track;
void dfs(int now)
{
	track.push_back(now);
	for(int i=0;i<num;++i){
		if(edges[now][i] == 1){
			edges[now][i] = -1;
			edges[i][now] = -1;
			dfs(i);
			edges[now][i] = 1;
			edges[i][now] = 1;

		}
	}
}

int main(void)
{
	cin >> num >> start;
	edges.resize(num);
	for(int i=0;i<num;++i){
		edges[i].resize(num, -1);
	}
	int input_get;
	int store = -1;
	while(cin >> input_get)
	{
		if(store == -1){
			store = input_get;
		}
		else{
			edges[store][input_get] = 1;
			edges[input_get][store] = 1;
			store = -1;
		}
	}
}