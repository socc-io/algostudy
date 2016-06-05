#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> pasw; // Answer, password of locker
vector<int> stat; // Status of locker
vector<int> dist; // pasw - stat, Distance between password and status of now

int GetDist(int a, int b)
{
	int delta = a - b;
	if(delta > 5) {
		delta -= 10;
	}
	else if(delta < -5) {
		delta += 10;
	}
	return delta;
}

void UpdateBetterDist(int index)
{
	int *di = &dist[index];
	if(*di > 5) {
		*di -= 10;
	}
	else if (*di < -5) {
		*di += 10;
	}
}

void DFS(int index)
{  
	int delta1=999;
	int delta2=999;
	if(index <= n-2) {
		delta1 = GetDist(dist[index], dist[index+1]);
		if(index <= n-3) {
			delta2 = GetDist(dist[index], dist[index+2]);
		}
	}
	  
}

int main(void)
{
	char stringBuffer[150];
	cin >> n;
	pasw.resize(n,0);
	stat.resize(n,0);
	dist.resize(n,0);

	cin >> stringBuffer;
	for(int i=0;i<n;++i) pasw[i] = stringBuffer[i] - '0';

	cin >> stringBuffer;
	for(int i=0;i<n;++i) stat[i] = stringBuffer[i] - '0';

	for(int i=0;i<n;++i) {
		dist[i] = pasw[i] - stat[i]
		UpdateBetterDist(i);
	}

	return 0;
} 