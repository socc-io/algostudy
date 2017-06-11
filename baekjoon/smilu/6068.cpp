
#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int capacity[52][52];

char buf1[10];
char buf2[10];

void find_route(vector<int>& route, int src, int dest)
{
	queue<int> Q;
	vector<bool> visited(52, false);
	vector<int> track(52, -1);
	Q.push(src);
	visited[src] = true;

	while( (!Q.empty()) ) {
		int v = Q.front(); Q.pop();

		for(int w=0; w<52; ++w) {
			if(capacity[v][w] > 0 && visited[w] == false) {
				Q.push(w);
				track[w] = v;
				visited[w] = true;
			}
		}
	}

	int cur = dest;
	deque<int> track_route;
	while(cur != -1) {
		track_route.push_front(cur);
		cur = track[cur];
	}

	route.clear();
	for(deque<int>::iterator it = track_route.begin(); it != track_route.end(); ++it) {
		route.push_back(*it);
	}

	// printf("track: ");
	// for(int i=0; i<26; ++i) printf("%d ", track[i]);
	// printf("\n");

	// printf("route found: ");
	// for(vector<int>::iterator it = route.begin(); it != route.end(); ++it) {
	// 	printf("%d ", *it);
	// } printf("\n");
}

int force_reverse(vector<int> &route)
{
	vector<int>::iterator prev_it, it;

	int min_capacity = -1;

	prev_it = route.begin();
	it = route.begin(); ++it;
	for(; it != route.end(); ++it, ++prev_it) {
		int v = (*prev_it);
		int w = (*it);
		if (min_capacity == -1 || min_capacity > capacity[v][w]) {
			min_capacity = capacity[v][w];
		}
	}

	prev_it = route.begin();
	it = route.begin(); ++it;
	for(; it != route.end(); ++it, ++prev_it) {
		int v = (*prev_it);
		int w = (*it);
		capacity[v][w] -= min_capacity;
		capacity[w][v] += min_capacity;
	}

	return min_capacity;
}

int char_to_idx(char z)
{
	if('A' <= z && z <= 'Z') {
		return z - 'A';
	}
	else {
		return z - 'a' + 26;
	}
}

int main(void)
{
	scanf("%d", &N);

	for(int i=0; i<52; ++i) for(int j=0; j<52; ++j) {
		capacity[i][j] = 0;
	}

	for(int i=0; i<N; ++i) {
		int capacity_;
		scanf("%s%s%d", buf1, buf2, &capacity_);
		char v = buf1[0];
		char w = buf2[0];

		capacity[char_to_idx(v)][char_to_idx(w)] += capacity_;
	}

	// printf("capacity matrix:\n");
	// for(int i=0; i<26; ++i) {
	// 	for(int j=0; j<26; ++j) {
	// 		printf("%3d ", capacity[i][j]);
	// 	} printf("\n");
	// }

	int force_sum = 0;

	vector<int> route; find_route(route, 0, 25);
	while(route[0] == 0) {
		force_sum += force_reverse(route); 
		find_route(route, 0, 25);
	}
	
	printf("%d\n", force_sum);

	return 0;
}