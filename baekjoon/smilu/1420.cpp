#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define INFINITE 0x7FFFFFFF

const int next_delta[4][2] = {
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

class Graph
{
public :
	int xsize;
	int ysize;
	vector< vector<int> > nodes;
	vector< pair<int, int> > position;
	vector<string> map;
	Graph(int xsize_, int ysize_) {
		xsize = xsize_;
		ysize = ysize_;
		nodes.resize(xsize*ysize*2);
	}
	int getIndex(int x, int y, int upper) {
		return (x*ysize) + y + (upper * xsize * ysize);
	}
	int getDistance(int a, int b)
	{
		a %= xsize * ysize;
		b %= xsize * ysize;
		int ax = position[a].first;
		int ay = position[a].second;
		int bx = position[b].first;
		int by = position[b].second;
		return abs(ax - bx) + abs(ay - by);
	}
	bool getInputAndBuild(int &start, int &end, vector< vector<int> > &node_store) {
		map.resize(xsize);
		position.resize(xsize * ysize);
		for(int i=0;i<xsize;++i) {
			cin >> map[i];
		}
		for(int i=0;i<xsize;++i) {
			for(int j=0;j<ysize;++j) {
				if(map[i][j] == '#') continue;
				int myindex = getIndex(i, j, 0);
				if(map[i][j] == 'K') start = myindex;
				else if(map[i][j] == 'H') end = myindex;
				nodes[getIndex(i,j,1)].push_back(myindex);
				position[myindex] = pair<int, int>(i, j);
				for(int k=0;k<4;++k) {
					int x = i + next_delta[k][0];
					int y = j + next_delta[k][1];
					if(0 <= x && x < xsize && 0 <= y && y < ysize &&
						map[x][y] != '#') {
						nodes[myindex].push_back(getIndex(x,y, map[x][y] == 'H' ? 0 : 1));
					}
				}
			}
		}
		int sx = position[start].first; int sy = position[start].second;
		int ex = position[end].first;   int ey = position[end].second;
		if((sy == ey && (sx == ex - 1 || sx == ex + 1)) || (sx == ex && (sy == ey - 1 || sy == ey + 1))) {
			return true;
		}
		node_store = nodes;
		return false;
	}
	bool find_augment(int pos, int end, vector<int> &augment) {
		int size = nodes.size();
		vector<int> track(size, -1);
		vector<int> done(size, 0);
		queue<int> Q;
		Q.push(pos);
		while(!(Q.empty())) {
			int f = Q.front();
			// cout << f << " ";
			Q.pop();
			if(done[f] == 1) continue;
			for(vector<int>::iterator it = nodes[f].begin(); it != nodes[f].end(); ++it) {
				if(done[*it] == 1) continue;
				Q.push(*it);
				track[*it] = f;
			}
			done[f] = 1;
		}
		if(track[end] == -1) return false;
		augment.clear();
		augment.push_back(end);
		while(true) {
			int b = augment.back();
			int n = track[b];
			augment.push_back(n);
			if(n == pos) break;
		}
		reverse(augment.begin(), augment.end());
		return true;
	}
	void FordFulkerson(int start, int end) {
		vector<int> augmenting;
		augmenting.reserve(xsize * ysize * 2);
		while(find_augment(start, end, augmenting)) {
			int augment_size = augmenting.size();
			for(int i=1;i<augment_size;++i) {
				int left = augmenting[i-1];
				int right = augmenting[i];
				nodes[left].erase(find(nodes[left].begin(), nodes[left].end(), right));
				nodes[right].push_back(left);
				/*sort(nodes[right].begin(), nodes[right].end(), [&](int a, int b) -> bool {
					return (getDistance(a, end) < getDistance(b, end));
				});*/
			}
			// cout << "Processed a path" << endl;
		}
	}
	void getReachable_DFS(int pos, vector<int> &r) {
		r[pos] = 1;
		for(vector<int>::iterator it = nodes[pos].begin(); it != nodes[pos].end(); ++it) {
			if(r[*it] != 1) getReachable_DFS((*it), r);
		}
	}
	void getReachable(int start, vector<int> &r) {
		r.resize(xsize * ysize * 2, 0);
		getReachable_DFS(start, r);
	}
	int getMincutCount(vector<int> &reach, vector< vector<int> > &origin) {
		int size = origin.size();
		int cnt = 0;
		for(int i=0;i<size;++i) {
			if(reach[i] == 0) continue;
			for(vector<int>::iterator it = origin[i].begin(); it != origin[i].end(); ++it) {
				if(reach[*it] == 0) {
					++cnt;
				}
			}
		}
		return cnt;
	}
};

int main(int argc, char** argv)
{
	int xsize, ysize;
	int start, end;
	vector< vector<int> > original_nodes;
	vector<int> reachable;
	cin >> xsize >> ysize;
	Graph graph(xsize, ysize);
	if(graph.getInputAndBuild(start, end, original_nodes)) {
		cout << -1 << endl;
		return 0;
	}
	// cout << "Graph build Complete" << endl;
	graph.FordFulkerson(start, end);
	// cout << "Ford Fulkerson Complete" << endl;
	graph.getReachable(start, reachable);
	// cout << "GetReachable Complete" << endl;
	int result = graph.getMincutCount(reachable, original_nodes);
	// cout << "Find Mincut Complete" << endl;
	cout << result << endl;
	return 0;
}