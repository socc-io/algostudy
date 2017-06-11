#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <stack>
#include <queue>
using namespace std;

int N, M, V;

template <class T>
struct Stack {
	stack<T> s;
	T pop() {
		T res = s.top();
		s.pop(); 
		return res;
	}
	void push(T val) {
		s.push(val);
	}
	int empty() { return s.empty(); }
};

template <class T>
struct Queue {
	queue<T> q;
	T pop() {
		T res = q.front();
		q.pop();
		return res;
	}
	void push(T val) {
		q.push(val);
	}
	int empty() { return q.empty(); }
};

int conn[1001][1001];
int visit[1001];

template <class T>
void search(T container)
{
	memset(visit, 0, sizeof(int)*1001);

	visit[V] = 1;
	container.push(V);

	while(!(container.empty())) {
		int f = container.pop();
		if (visit[f]) continue;
		printf("%d ", f);
		visit[f] = 1;
		for(int i=0; i<N; ++i) {
			if(conn[f][i]) {
				container.push(i);
			}
		}
	}
	printf("\n");
}

int main(void)
{
	scanf("%d%d%d", &N, &M, &V);

	memset(conn, 0, sizeof(int)*1001*1001);
	for(int i=0; i<M; ++i) {
		int from, to;
		scanf("%d%d", &from, &to);
		conn[from-1][to-1] = 1;
	}

	Queue<int> q;
	search(q);

	Stack<int> s;
	search(s);
}