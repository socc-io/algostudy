#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum { NOEXIST = 0, EXIST };
#define INFINITE 9999999

/*
Euler

In this problem, we must judge if a graph can be drawed at once, for pen not to go back and be apart of paper.
Euler, the famous mathmatician, proved that a graph that can be drawed at once must have two or zero vertices having
the odd number of edges.
In the case that the graph has two vertices having the odd number of edges, the drawing must be started at the one of the vertices
having the odd number of edges, and ended at the other.

To solve this problem :
First, count the number of vertices having the odd number of edges.
if the number is two, use DFS(Depth First Search) with the first vertex being one of the vertices having the odd number of edges.
else if the number is zero, use DFS with the first vertex being all of the vertices.
else, the graph can't be drawed at once.
*/

vector< vector<int> > rn; // Road Network Matrix
vector< vector<int> > roadmap; // Road map;
int numOfVertices; // the number of vertices
int numOfRoads; // the number of roads

vector<int> tracker;
bool DFSEuler(int position)
{
	if (tracker.size() == numOfRoads) {
		tracker.push_back(position);
		return true;
	}
	tracker.push_back(position);
	for (int destindex = 0; destindex<roadmap[position].size(); ++destindex) {
		int dest = roadmap[position][destindex];
		if (rn[position][dest] == EXIST) {
			rn[position][dest] = NOEXIST;
			rn[dest][position] = NOEXIST;
			bool finded = DFSEuler(dest);
			rn[position][dest] = EXIST;
			rn[dest][position] = EXIST;
			if (finded) {
				return true;
			}
		}
	}
	tracker.pop_back();
	return false;
}

int main(int argc, char **argv)
{
	cin >> numOfVertices >> numOfRoads; // Input the number of vertices and roads
	rn.resize(numOfVertices);  // Allocate proper size of network and roadmap
	roadmap.resize(numOfVertices);
	for (int i = 0; i < numOfVertices; ++i) {
		rn[i].resize(numOfVertices, NOEXIST);
	}
	for (int i = 0; i < numOfRoads; ++i) { // Input the road network.
		int from, to;
		cin >> from >> to;
		from--;
		to--;
		rn[from][to] = EXIST;
		rn[to][from] = EXIST;
		roadmap[from].push_back(to);
		roadmap[to].push_back(from);
	}
	vector<int> gispot;
	for (int i = 0; i < numOfVertices; ++i) { // Count the number of vertices having odd number of edges.(Gispot)
		if (roadmap[i].size() & 1) {
			gispot.push_back(i);
		}
	}
	if (gispot.size() == 2) { // When the number of gispot is two
		tracker.reserve(1000);
		tracker.clear();
		bool isSuccess = DFSEuler(gispot[0]);
		if (!isSuccess)
		{
			cout << "0" << endl;
		}
		else {
			for (int i = 0; i<tracker.size(); ++i) {
				cout << tracker[i] + 1 << " ";
			}
			cout << endl;
		}
	}
	else if (gispot.empty()) { // There isn't any gispot
		tracker.reserve(1000);
		int i;
		for (i = 0; i<numOfVertices; ++i) {
			tracker.clear();
			if (DFSEuler(i)) break;
		}
		for (int i = 0; i<tracker.size(); ++i) {
			cout << tracker[i] + 1 << " ";
		}
		cout << endl;
	}
	else { // the number of gispot isn't 2 and 0, the euler path can't exist
		cout << "0" << endl;
	}
	return 0;
}