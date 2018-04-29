
#include <cstdio>
#include <cstdlib>

#include <vector>

using namespace std;

int A[101];
int B[101];
int C[101][101];
int N, M;

struct Edge {
	int weight;
	int cost;
};

struct Node {
	vector<Edge> edges;
	int d;
};

Node nodes[202];

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) {
		scanf("%d", A + i);
	}
	for(int i=0; i<M; ++i) {
		scanf("%d", B + i);
	}
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			scanf("%d", C[i] + j);
		}
	}

}