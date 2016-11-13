#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

#define INF 0x7FFFFFFF

struct edge {
	int a;
	int b;
	int w;
};

int findRoot(int pos, vector<int> &chain)
{
	while(chain[pos] != pos) pos = chain[pos];
	return pos;
}

int main(int argc, char** argv)
{
	int N, M;
	cin >> N >> M;
	++N; ++M;
	deque<edge> edges;
	for(int i=0;i<M;++i) {
		int a, b, w;
		cin >> a >> b >> w;
		if(w == 1) edges.push_back ({a,b,w});
		else       edges.push_front({a,b,w});
	}
	vector<int> group_chain(N);
	for(int i=0;i<N;++i) group_chain[i] = i;
	int select_cnt = 0;
	int min_cost = 0;
	int edge_cur = 0;
	while(select_cnt < N-1) {
		edge now_edge = edges[edge_cur++];
		int a_root = findRoot(now_edge.a, group_chain);
		int b_root = findRoot(now_edge.b, group_chain);
		if(a_root == b_root) continue;
		if(a_root < b_root) group_chain[b_root] = a_root;
		else                group_chain[a_root] = b_root;
		min_cost += now_edge.w;
		++select_cnt; 
	}

	for(int i=0;i<N;++i) group_chain[i] = i;
	select_cnt = 0;
	int max_cost = 0;
	edge_cur = M-1;
	while(select_cnt < N-1) {
		edge now_edge = edges[edge_cur--];
		int a_root = findRoot(now_edge.a, group_chain);
		int b_root = findRoot(now_edge.b, group_chain);
		if(a_root == b_root) continue;
		if(a_root < b_root) group_chain[b_root] = a_root;
		else                group_chain[a_root] = b_root;
		max_cost += now_edge.w;
		++select_cnt;
	}

	cout << (max_cost + min_cost) * (max_cost - min_cost) << endl;
	return 0;
}