#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int mapsize;
int numSpot;
vector< pair<int, int> > spot;
vector< vector<int> > mincost;
vector< vector<int> > dist;
vector< vector< pair<int, int> > > tracker;
int min(int a, int b)
{
	if (a<b) {
		return a;
	}
	return b;
}

int main(void)
{
	cin >> mapsize >> numSpot;
	numSpot += 2;
	spot.resize(numSpot);
	for (int i = 2; i < numSpot; ++i) {
		cin >> spot[i].first >> spot[i].second;
		spot[i].first--;
		spot[i].second--;
	}
	mincost.resize(numSpot);
	dist.resize(numSpot);
	tracker.resize(numSpot);
	for (int i = 0; i<numSpot; ++i)
	{
		mincost[i].resize(numSpot, 999999);
		dist[i].resize(numSpot, -1);
		tracker[i].resize(numSpot);
	}
	spot[0].first = 0;
	spot[0].second = 0;
	spot[1].first = mapsize - 1;
	spot[1].second = mapsize - 1;
	mincost[0][1] = 0;
	for (int i = 0; i<numSpot; ++i)
	{
		for (int j = 0; j<numSpot; ++j)
		{
			dist[i][j] = abs(spot[i].first - spot[j].first) + abs(spot[i].second - spot[j].second);
			dist[j][i] = dist[i][j];
		}
	}
	for (int i = 2; i < numSpot; ++i)
	{
		for (int j = 0; j < i - 1; ++j)
		{
			int newval;
			newval = mincost[j][i - 1] + dist[i - 1][i];
			if (newval < mincost[j][i]) {
				mincost[j][i] = newval;
				tracker[j][i].first = j;
				tracker[j][i].second = i - 1;
			}
			newval = mincost[j][i - 1] + dist[j][i];
			if (newval < mincost[i - 1][i]) {
				mincost[i - 1][i] = newval;
				tracker[i - 1][i].first = j;
				tracker[i - 1][i].second = i - 1;
			}
		}
	}
	int min = 999999;
	int minindex = -1;
	for (int i = 0; i<numSpot; ++i)
	{
		if (min > mincost[i][numSpot - 1]) {
			min = mincost[i][numSpot - 1];
			minindex = i;
		}
	}
	cout << min << endl;
	pair<int, int> trackpos;
	vector< pair<int, int> > trackstack;
	trackpos.first = minindex;
	trackpos.second = numSpot - 1;
	while (trackpos.first != 0 || trackpos.second != 1) {
		trackstack.push_back(trackpos);
		trackpos = tracker[trackpos.first][trackpos.second];
	}
	trackstack.push_back(trackpos);
	vector< pair<int, int> > routestack;
	for (int i = trackstack.size() - 1; i >= 0; --i) {
		routestack.push_back(trackstack[i]);
	}
	int now = 2;
	for (int i = 0; i < routestack.size()-1; ++i) {
		if (routestack[i].first == routestack[i + 1].first) {
			cout << now << endl;
		}
		else {
			now = 3 - now;
			cout << now << endl;
		}
	}
}