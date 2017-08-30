#include <cstdio>
#include <vector>

#include <queue>

using namespace std;

int N;

char c_tmp1, c_tmp2;
int tmp;

vector< vector< pair<char, int> > > edges;

inline int convertNameToIndex(char ch)
{
	if('a' <= ch && ch <= 'z') return ch - 'a' + 26;
	return ch - 'A';
}

int main(void)
{
	int N;
	scanf("%d", &N);
	edges.resize(52);
	for(int i = 0; i < N; ++i){
		c_tmp1 = convertNameToIndex(getchar()); getchar();
		c_tmp2 = convertNameToIndex(getchar()); getchar();
		scanf("%d", &tmp);
		edges[c_tmp1].push_back(make_pair(c_tmp2, tmp));
		edges[c_tmp2].push_back(make_pair(c_tmp1, 0));
	}

	int cap_sum = 0;

	while(true) {
		printf("loop!\n");
		queue<int> Q;
		vector<int> tracker(52, -1);

		Q.push(0);

		bool found = false;
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			for(auto it = edges[u].begin(); it == edges[u].end(); ++it) {
				int v = it->first;
				int cap = it->second;
				if(cap <= 0) continue;
				if(tracker[v] != -1) continue;
				tracker[v] = u;
				Q.push(v);

				if(v == 25) {
					found = true;
					break;
				}
			}
			if(found) break;
		}

		if(tracker[25] == -1) break;

		int min_cap = 0x7FFFFFFF;
		for(int cur = 25; cur != 0; cur = tracker[cur]) {
			int u = tracker[cur];
			int v = cur;
			for(auto it = edges[u].begin(); it != edges[u].end(); ++it) {
				if(it->first == v) {
					int cap = it->second;
					if(min_cap > cap) min_cap = cap;
					break;
				}
			}
		}
		cap_sum += min_cap;

		for(int cur = 25; cur != 0; cur = tracker[cur]) {
			int u = tracker[cur];
			int v = cur;
			for(auto it = edges[u].begin(); it != edges[u].end(); ++it) {
				if(it->first == v) {
					it->second -= min_cap;
					break;
				}
			}
			for(auto it = edges[v].begin(); it != edges[v].end(); ++it) {
				if(it->first == u) {
					it->second += min_cap;
					break;
				}
			}
		}
	}

	printf("%d", cap_sum);
}