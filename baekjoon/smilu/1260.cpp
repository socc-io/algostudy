#include <stdio.h>

#pragma warning(disable:4996)

int main(int argc, char** argv)
{
	int vertex_num, edge_num, starter;
	int vec[100000];
	int que[100000];
	int vec_end = 1;
	int que_start = 0;
	int que_end = 1;
	scanf("%d %d %d", &vertex_num, &edge_num, &starter);
	--starter;
	vec[0] = starter;
	que[0] = starter;
	int **graph = new int*[vertex_num];
	int *entered = new int[vertex_num];
	for (int i = 0; i < vertex_num; ++i) {
		graph[i] = new int[vertex_num];
		entered[i] = 0;
		for (int j = 0; j < vertex_num; ++j) {
			graph[i][j] = 0;
		}
	}
	for (int i = 0; i < edge_num; ++i) {
		int from, to;
		scanf("%d %d", &from, &to);
		--from; --to;
		graph[from][to] = 1;
		graph[to][from] = 1;
	}

	while (vec_end != 0) {
		--vec_end;
		int last = vec[vec_end];
		if (entered[last] == 1) continue;
		printf("%d ", last + 1);
		entered[last] = 1;
		for (int i = vertex_num-1; i >= 0; --i) {
			if (graph[last][i] == 1) {
				vec[vec_end++] = i;
			}
		}
	}
	for (int i = 0; i < vertex_num; ++i) entered[i] = 0;
	printf("\n");
	while (que_start < que_end) {
		int first = que[que_start++];
		if (entered[first] == 1) continue;
		printf("%d ", first + 1);
		entered[first] = 1;
		for (int i = 0; i < vertex_num; ++i) {
			if (graph[first][i] == 1) {
				que[que_end++] = i;
			}
		}
	}

	for (int i = 0; i < vertex_num; ++i) {
		delete[] graph[i];
	}
	delete[] graph;
	delete[] entered;
	return 0;
}