#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITE 999999
#define TRACKER_SIZE 10000
#define MAX_VERTEXNUM 20000

int n; // the number of cages
int m; // the number of people
int rn[MAX_VERTEXNUM][MAX_VERTEXNUM]; // Residual Network
vector< vector<int> > vertexmap;
vector<int> cageindex; // save now cage index
vector<int> pigNum;
int vertexnum;
int sink; // 1
int source; // 0

int fAugmentTracker[TRACKER_SIZE];
int fAugmentTrackerIndex = 0;
vector<bool> visited;

bool augment(int pos)
{
	vector<int> toVisit;
	toVisit.reserve(vertexnum);
	fAugmentTracker[fAugmentTrackerIndex++] = pos;
	visited[pos] = true;
	if (pos == sink) {
		return true;
	}
	int vertexmapSize = vertexmap[pos].size();
	for (int i = 0; i < vertexmapSize; ++i) {
		int trg = vertexmap[pos][i];
		if (rn[pos][trg] > 0) {
			if (!visited[trg])
			{
				toVisit.push_back(trg);
			}
		}
	}
	// todo : toVisit 정렬한 후에, 큰 것 부터 augment에 넣음
	int toVisitNum = toVisit.size();
	for (int i = 0; i < toVisitNum; ++i) {

	}
	visited[pos]=false;
	return false;
}

void FordFulkerson(int start)
{
	visited.resize(vertexnum, false);
	fAugmentTrackerIndex = 0;
	while (augment(start)) {
		int minflow = INFINITE;
		for (int i = 0; i < fAugmentTrackerIndex - 1; ++i) { // Find minimum value in tracker
			int nowflow = rn[fAugmentTracker[i]][fAugmentTracker[i + 1]];
			if (nowflow < minflow) {
				minflow = nowflow;
			} 
		}
		for (int i = 0; i < fAugmentTrackerIndex - 1; ++i) { // Update RN
			int left = fAugmentTracker[i];
			int right = fAugmentTracker[i + 1];
			rn[left][right] -= minflow;
			rn[right][left] += minflow;
		}
		fAugmentTrackerIndex = 0; // Reset Tracker
		for (int i = 0; i < vertexnum; ++i) {
			visited[i] = false;
		}
	}
}

int GetMaxFlow()
{
	int sum = 0;
	for (int i = 0; i < vertexnum; ++i) {
		sum += rn[i][source];
	}
	return sum;
}

inline void makeEdge(int a, int b, int w = INFINITE)
{
	rn[a][b] = w;
	vertexmap[a].push_back(b);
	vertexmap[b].push_back(a);
}

int main(void)
{
	cin >> n >> m;
	source = 0;
	sink = 1;
	int base = 2;
	int prevCustomer = 0;
	vector<int> keyvals;
	vertexmap.resize(MAX_VERTEXNUM);
	keyvals.reserve(n);
	keyvals.clear();
	cageindex.resize(n);
	pigNum.resize(n);
	for (int i = 0; i < n; ++i) { // Get Input about the number of pigs in cages
		cin >> pigNum[i];
		cageindex[i] = source;
	}
	for (int deal = 0; deal < m; ++deal) {
		int keynum; // get keynum
		cin >> keynum;
		if (keynum == 0) { // if key num is zero, continue
			int tmp;
			cin >> tmp;
			continue;
		}
		/////////////////////
		if (deal != 0) {
			for (int key = 0; key < keyvals.size(); ++key) { // Make edge from prev customer to now cage
				cageindex[keyvals[key]] = prevCustomer;
			}
		}
		keyvals.clear();
		for (int key = 0; key < keynum; ++key) { // Make edge from cage to customer
			int keyval;
			cin >> keyval;
			keyval--;
			keyvals.push_back(keyval);
			if (cageindex[keyval] != source) {
				makeEdge(cageindex[keyval], base); // now base is customer
			}
			else {
				makeEdge(source, base, pigNum[keyval]+rn[source][base]);
			}
		}
		int tmp;
		cin >> tmp; // Make edge from customer to sink
		makeEdge(base, sink, tmp);
		prevCustomer = base;
		base++;
	}
	vertexnum = base;
	// printf("vertexnum: %d\n", vertexnum);
	FordFulkerson(source);
	int maxflow = GetMaxFlow();
	printf("%d\n", maxflow);

	return 0;
}
