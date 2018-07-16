
#include <cstdio>

#include <vector>
#include <queue>

using namespace std;

typedef struct Edge Edge;

struct Node {
	int idx;
	Node* back;
	vector<Edge*> p_edges;
};

struct Edge {
	int w;
	Node* from;
	Node* to;
	Edge* opposite;
	Edge(Node* from, Node* to, int w): from(from), to(to), w(w) {}
};

struct Graph {
	int node_num;
	Node* nodes;
	vector<Edge*> p_edges;
	Graph(int node_num): node_num(node_num) {
		nodes = new Node[node_num];
		for(int i=0; i<node_num; i++) {
			nodes[i].idx = i;
		}
	}
	void connect(int from_idx, int to_idx, int w, int bw = 0) {
		Node* p_from = nodes + from_idx;
		Node* p_to = nodes + to_idx;
		Edge* p_edge = new Edge(p_from, p_to, w);
		Edge* p_back_edge = new Edge(p_to, p_from, bw);
		p_edges.push_back(p_edge);
		p_edges.push_back(p_back_edge);
		p_from->p_edges.push_back(p_edge);
		p_to->p_edges.push_back(p_back_edge);
	}
	void find_path(int src_idx, int dest_idx) {

	}
};

int main(void)
{
	printf("Hello world!\n");

	return 0;
}