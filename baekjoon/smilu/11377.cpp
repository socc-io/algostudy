
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <queue>

#define MAX_WORKER 1000
#define MAX_WORK 1000

// #define DEBUG

using namespace std;

int n;  // The number of worker
int m;  // The number of work
int k;  // The number of worker who can do 2 works.

struct Edge;

struct Node {
	vector<Edge*> p_edges;
	Edge* backedge;
#ifdef DEBUG
    char* name;
    int idx;
#endif
};

struct Edge {
	Node* from;
	Node* to;
	Edge* op;
	int w;
	Edge(Node* from, Node* to): from(from), to(to) {
		op = NULL;
		w = 0;
	}
};

Node n_start;
Node n_more;
Node n_worker[MAX_WORKER];
Node n_work[MAX_WORK];
Node n_end;

void connect(Node* from, Node* to, int w)
{
	Edge* e1 = new Edge(from, to);
	Edge* e2 = new Edge(to, from);

	e1->op = e2;
	e2->op = e1;

	e1->w = w;

	from->p_edges.push_back(e1);
	to->p_edges.push_back(e2);
}

void clear_backedge() {
	n_start.backedge = NULL;
    n_more.backedge = NULL;
	for(int i = 0; i < MAX_WORKER; i++) {
		n_worker[i].backedge = NULL;
	}
	for(int i = 0; i < MAX_WORK; i++) {
		n_work[i].backedge = NULL;
	}
	n_end.backedge = NULL;
}

int findpath(Node* from, Node* to)
{
	int found_end = 0;
	int min_w;
	Node* cur;
	queue<Node*> q;
	q.push(from);
	clear_backedge();
	
	while(!q.empty()) {
		Node* u = q.front();
		q.pop();
#ifdef DEBUG
		printf("popped: %s%d\n", u->name, u->idx);
#endif
		for(auto it = u->p_edges.begin(); it != u->p_edges.end(); it++) {
			Edge* e = (*it);
			Node* v = e->to;

			if (e->w <= 0) continue;
			if (v->backedge != NULL) continue;
            if (v == from) continue;

			v->backedge = e;
#ifdef DEBUG
			printf("set backedge %s%d -> %s%d\n", u->name, u->idx, v->name, v->idx);
#endif
			if (v == to) {
				found_end = 1;
				break;
			}
			q.push(v);
		}
		if (found_end == 1) {
			break;
		}
	}

	if (found_end == 1) {
#ifdef DEBUG
		printf("Found path in findpath\n");
#endif
		min_w = to->backedge->w;
		for (Node* cur = to; cur->backedge != NULL; cur = cur->backedge->from) {
			if (cur->backedge->w < min_w) {
				min_w = cur->backedge->w;
			}
		}
	} else {
#ifdef DEBUG
		printf("Failed to findpath\n");
#endif
		min_w = 0;
	}

	return min_w;
}

int main(void)
{
	int work_num;
	int work_idx;
	int min_w;
	int sum_w = 0;

#ifdef DEBUG
    n_start.name = "start";
    n_more.name = "more";
    n_end.name = "end";
    for(int i = 0; i < MAX_WORK; i++) {
        n_work[i].name = "work";
        n_work[i].idx = i + 1;
    }
    for(int i = 0; i < MAX_WORKER; i++) {
        n_worker[i].name = "worker";
        n_worker[i].idx = i + 1;
    }
#endif

	scanf("%d%d%d", &n, &m, &k);
    connect(&n_start, &n_more, k);
	for(int i = 0; i < n; i++) {
		scanf("%d", &work_num);
		for(int j = 0; j < work_num; j++) {
			scanf("%d", &work_idx);
			work_idx--;
			connect(n_worker + i, n_work + work_idx, 1);
		}
		connect(&n_start, n_worker + i, 1);
        connect(&n_more, n_worker + i, 1);
	}
	for(int i = 0; i < m; i++) {
		connect(n_work + i, &n_end, 1);
	}

	while ((min_w = findpath(&n_start, &n_end)) > 0) {
		sum_w += min_w;
#ifdef DEBUG
		printf("found min_w: %d\n", min_w);
#endif
		for(Node* cur = &n_end; cur->backedge != NULL; cur = cur->backedge->from) {
#ifdef DEBUG
            printf("    %s%d\n", cur->name, cur->idx);
#endif
			cur->backedge->w -= min_w;
			cur->backedge->op->w += min_w;
		}
	}

	printf("%d\n", sum_w);

	return 0;
}