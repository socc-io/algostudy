#include <iostream>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

bool findAugment(vector< set<int> > &graph, vector<int> &augment)
{
	int size = graph.size();
	queue<int> Q;
	Q.push(0);
	vector<int> track(size);
	for(int i=0;i<size;++i) track[i] = i;
	while(!(Q.empty())) {
		int front = Q.front(); Q.pop();
		cout << front << " ";
		if(front == size-1) {
			augment.clear();
			int cur = front;
			while(cur != 0) {
				augment.push_back(cur);
				cur = track[cur];
			}
			augment.push_back(cur);
			reverse(track.begin(), track.end());
			return false;
		}
		for(auto it = graph[front].begin(); it != graph[front].end(); ++it) {
			if(track[*it] == (*it)) {
				track[*it] = front;
				Q.push(*it);
			}
		}
	}
	return true;
}

int maxFlow(vector< set<int> > &graph)
{
	int size = graph.size();
	vector<int> augment;
	augment.reserve(size);
	int cnt = 0;
	while(true) {
		if(findAugment(graph, augment)) break;
		int aug_size = augment.size();
		for(int i=0;i<aug_size-1;++i) {
			int left  = augment[i];
			int right = augment[i+1];
			graph[left].erase(right);
			graph[right].insert(left);
		}
		++cnt;
	}
	return cnt;
}

int main(void)
{
	int n, m;
	cin >> n >> m;
	int graph_size = n + m + 2;
	int sink_idx = graph_size - 1;
	vector< set<int> > graph(graph_size);
	for(int i=0;i<n;++i) {
		graph[0].insert(1+i);
	}
	for(int i=0;i<m;++i) {
		graph[1+n+i].insert(sink_idx);
	}
	for(int i=0;i<n;++i) {
		int num;
		cin >> num;
		for(int j=0;j<num;++j) {
			int val;
			cin >> val; --val;
			graph[1+i].insert(1+n+val);
		}
	}
	int maxf = maxFlow(graph);
	cout << maxf << endl;
}