/*
 * site: https://www.acmicpc.net/problem/11377
 * author: smilu97
 * date: 2018-06-24
 */

/*

문제
강호네 회사에는 직원이 N명이 있고, 해야할 일이 M개가 있다. 직원은 1번부터 N번까지 번호가 매겨져 있고, 일은 1번부터 M번까지 번호가 매겨져 있다.

각 직원은 한 개의 일만 할 수 있고, 각각의 일을 담당하는 사람은 1명이어야 한다. 단, N명 중에서 K명은 일을 최대 2개할 수 있다.

각각의 직원이 할 수 있는 일의 목록이 주어졌을 때, M개의 일 중에서 최대 몇 개를 할 수 있는지 구하는 프로그램을 작성하시오.

입력
첫째 줄에 직원의 수 N과 일의 개수 M, 일을 2개할 수 있는 직원의 수 K가 주어진다. (1 ≤ N, M ≤ 1,000, 1 ≤ K ≤ N)

둘째 줄부터 N개의 줄의 i번째 줄에는 i번 직원이 할 수 있는 일의 개수와 할 수 있는 일의 번호가 주어진다.

출력
첫째 줄에 강호네 회사에서 할 수 있는 일의 개수를 출력한다.

예제 입력 1 
5 5 1
3 1 2 3
3 1 2 3
1 5
1 5
1 5
예제 출력 1 
4

*/

#include <cstdio>

#include <vector>
#include <queue>

using namespace std;

int n, m, k;

typedef struct edge {
	int w; // weight
	struct node* from;
	struct node* to;
	struct edge* rev;
} edge;

typedef struct node {
	edge* back;
	vector<edge*> edges;
} node;

node source;
node start;
node sink;
node emp[1000];
node work[1000];

edge edge_pool[1002000];
int  edge_pool_idx = 1;

void connect(node* from, node* to, int weight)
{
	edge* e = edge_pool + (edge_pool_idx++);
	edge* r = edge_pool + (edge_pool_idx++);
	e->from = from;
	e->to = to;
	e->w = weight;
	r->from = to;
	r->to = from;
	r->w = 0;
	e->rev = r;
	r->rev = e;
	from->edges.push_back(e);
	to->edges.push_back(r);
}

void clear_backs() {
	source.back = 0;
	start.back = 0;
	sink.back = 0;
	for(int i=0; i<1000; ++i) {
		emp[i].back = 0;
		work[i].back = 0;
	}
}

edge* path[2003];
int path_idx = 0;
int path_find(node* ps, node* pe)
{
	queue<node*> q;
	bool b = false;
	q.push(ps);

	path_idx = 0;
	clear_backs();

	while(!q.empty()) {
		node* p = q.front();
		q.pop();
		for(auto it = p->edges.begin(); it != p->edges.end(); ++it) {
			edge* e = (*it);
			node* n = e->to;
			if (n->back != NULL) continue;
			n->back = e;
			if (n == pe) {
				b = true;
				break;
			}
			q.push(n);
		}
		if (b) break;
	}

	if (pe->back == 0)
		return -1;

	node* cur = pe;
	while(cur != ps) {
		path[path_idx++] = cur->back;
		cur = cur->back->from;
	}

	return 0;
}

int walk()
{
	edge* ecur;

	if(path_find(&source, &sink))
		return 0;

	printf("path found\n");

	int mf = sink.back->w;
	ecur = sink.back;
	while(ecur != 0) {
		if (ecur->w < mf) {
			mf = ecur->w;
		}
		ecur = ecur->from->back;
	}

	printf("mf found\n");

	ecur = sink.back;
	while(ecur != 0) {
		ecur->w -= mf;
		ecur->rev->w += mf;
		ecur = ecur->from->back;
	}

	return mf;
}

int main(void)
{
	int work_num, work_idx, f, fs = 0;

	scanf("%d%d%d", &n, &m, &k);

	connect(&source, &start, n + k);
	for(int i=0; i<n; ++i) {
		connect(&start, emp + i, 2);
		scanf("%d", &work_num);
		for(int j=0; j<work_num; ++j) {
			scanf("%d", &work_idx);
			--work_idx;
			connect(emp + i, work + work_idx, 1);
		}
	}
	for(int i=0; i<m; ++i) {
		connect(work + i, &sink, 1);
	}

	printf("connected\n");
	while((f = walk()) != 0) {
		fs += f;
		printf("f: %d\n", f);
	}

	printf("%d", fs);

	return 0;
}