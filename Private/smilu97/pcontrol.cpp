#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> cn; // Capacity network
vector<vector<int>> fn; // Flow network
vector<vector<int>> rn; // Residual network
vector<pair<int,int>> roadnum;
vector<int> minimumcut;
vector<bool> tight;
int maxflow = -1;

int swap(int &a, int &b) {
	int c = a;
	a = b;
	b = c;
}

int fftracker[1000];
int fftracker_index = 0;
bool FordFulkerson(int pos)
{
	fftracker[fftracker_index++] = pos;
	if(pos == n-1) {
		int minflow = 999999;
		for(int i=0;i<fftracker_index-1;++i) { // Find Minimum flow of finded track
			if(rn[i][i+1] < minflow) {
				minflow = rn[i][i+1];
			}
		}
		for(int i=0;i<fftracker_index-1;++i) {
			rn[i][i+1] -= minflow;
			rn[i+1][i] += minflow;
			fn[i][i+1] += minflow;
		}
		return true;
	}
	for(int i=0;i<n;++i) {
		if(rn[pos][i] > 0) {
			if(FordFulkerson(i)) {
				return true;
			}
		}
	}
	fftracker_index--;
	return false;
}

int main(void)
{
	cin >> n >> m;
	cn.resize(n);
	fn.resize(n);
	rn.resize(n);
	roadnum.resize(m);
	tight.resize(m);
	for(int i=0;i<n;++i) {
		cn[i].resize(n, 0);
		fn[i].resize(n, 0);
		rn[i].resize(n, 0);
	}
	for(int i=0;i<m;++i) {
		int a, b, c;
		cin >> a >> b >> c;
		if(a > b) swap(a,b);
		cn[a][b] = c;
		rn[a][b] = c;
		roadnum[i].first = a;
		roadnum[i].second = b
;	}
	while(FordFulkerson(0));
	maxflow = 0;
	for(int i=0;i<m;++i){
		maxflow += rn[i][0];
	}
	for(int i=0;i<m;++i) {
		tight[i] = rn[roadnum[i].first][roadnum[i].second] == 0;
	}
	int tsum = 0;
	minimumcut.clear();
	while(tsum < maxflow) {
		int maxvalue = -1;
		int maxindex;
		for(int i=0;i<m;++i) {
			if(tight[i]) {
				if(maxvalue < rn[roadnum[i].second][roadnum[i].first]) {
					maxvalue = rn[roadnum[i].second][roadnum[i].first];
					maxindex = i;
				}
			}
		}
		tight[maxindex] = false;
		tsum += maxvalue;
		if(tsum > maxflow) {
			tsum -= maxvalue;
		}
		else {
			minimumcut.push_back(i);
		}
	}
	cout << maxflow << " " << minimumcut.size() << endl;
	for(int i=0;i<minimumcut.size();++i) {
		cout << minimumcut[i] << endl;
	}
	return 0;
}