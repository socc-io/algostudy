#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool find_augment(vector< vector<int> > &graph, vector<int> &augment)
{
	int size = graph.size();
	vector<int> track(size);
	for(int i=0;i<size;++i) track[i] = i;
	queue<int> Q;
	Q.push(0);
	while(!(Q.empty())) {
		int front = Q.front(); Q.pop();
		if(front == size-1) {
			augment.clear();
			int cur = front;
			while(cur != 0) {
				augment.push_back(cur);
				cur = track[cur];
			}
			augment.push_back(cur);
			reverse(augment.begin(), augment.end());
			return false;
		}
		for(int i=0;i<size;++i) {
			if(graph[front][i] && track[i] == i) {
				Q.push(i);
				track[i] = front;
			}
		}
	}
	return true;
}

int maxFlow(vector< vector<int> > &graph)
{
	vector<int> augment_path;
	int cnt = 0;
	while(true) {
		if(find_augment(graph, augment_path)) {
			break;
		}
		int augment_size = augment_path.size();
		for(int i=0;i<augment_size-1;++i) {
			graph[augment_path[i]][augment_path[i+1]] = 0;
			graph[augment_path[i+1]][augment_path[i]] = 1;
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
	int source_idx = 0;
	int sink_idx = graph_size - 1;
	vector< vector<int> > graph(graph_size, vector<int>(graph_size, 0));
	for(int i=0;i<n;++i) {
		graph[source_idx][1+i] = 1;
	}
	for(int i=0;i<m;++i) {
		graph[1+n+i][sink_idx] = 1;
	}
	for(int i=0;i<n;++i) {
		int num;
		cin >> num;
		for(int j=0;j<num;++j) {
			int val;
			cin >> val; --val;
			graph[1+i][1+n+val] = 1;
		}
	}
	int maxf = maxFlow(graph);
	cout << maxf << endl;
	return 0;	
}