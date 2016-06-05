#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INFINITE 0x7FFFFFFF

class Road {
public :
	int dest;
	int distance;
};
class Spot {
public :
	vector<Road> roads;
};

int spotnum;
int roadnum;
int startspot;
vector<int> did;
Spot *spots;
int  *sd; // Shortest Distance
vector<int> *sr; // Shortest Route
bool *bdid;

int main(void)
{
	cin >> spotnum >> roadnum >> startspot;
	startspot--;
	spots = new Spot[spotnum];
	sd = new int[spotnum];
	sr = new vector<int>[spotnum];
	bdid = new bool[spotnum];
	for (int i = 0; i < roadnum; ++i) {
		int from;
		Road tmproad;
		cin >> from >> tmproad.dest >> tmproad.distance;
		from--;
		tmproad.dest--;
		spots[from].roads.push_back(tmproad);
	}
	for (int i = 0; i < spotnum; ++i) {
		bdid[i] = false;
	}
	did.push_back(startspot);
	bdid[startspot] = true;
	for (int i = 0; i < spotnum; ++i) {
		sd[i] = INFINITE;
	}
	sd[startspot] = 0;
	sr[startspot].push_back(startspot);

	for (int i = 1; i < spotnum; ++i) {
		int bestspot;
		int bestdest;
		int bestdistance = INFINITE;
		for (vector<int>::iterator it = did.begin(); it != did.end(); ++it) {
			for (vector<Road>::iterator it2 = spots[*it].roads.begin(); it2 != spots[*it].roads.end(); ++it2) {
				if (bdid[it2->dest]) continue;
				int newdistance = sd[*it] + it2->distance;
				if (newdistance < bestdistance) {
					bestdistance = newdistance;
					bestdest = it2->dest;
					bestspot = *it;
				}
			}
		}
		if (bestdistance != INFINITE) {
			sd[bestdest] = bestdistance;
			sr[bestdest] = sr[bestspot];
			sr[bestdest].push_back(bestdest);
			did.push_back(bestdest);
			bdid[bestdest] = true;
		}
		else {
			cout << "Couldn't find any route" << endl;
		}
	}
	for (int i = 0; i < spotnum; ++i) {
		// cout << i + 1 << " : ";
		for (vector<int>::iterator it = sr[i].begin(); it != sr[i].end(); ++it) {
			cout << *it + 1 << " ";
		}
		cout << endl;
	}

	delete[] spots;
	delete[] sr;
	delete[] sd;
	delete[] bdid;
	return 0;
}