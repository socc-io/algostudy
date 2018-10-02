
#include <cstdio>
#include <cstdlib>

#include <algorithm>

#define UNDEFINED -1
#define LOCKED -2

using namespace std;

int n;
int num[50];
int mat[50][50];
int conn[50];
int visited[50];
int prime[2001];
int ans[50];
int ans_num;

int make_connection(int idx)
{
	if (visited[idx] == 1) return UNDEFINED;
	visited[idx] = 1;
	for (int i = 1; i < n; i++) {
		if (mat[idx][i]) continue;
		if (conn[i] == UNDEFINED || make_connection(conn[i]) != UNDEFINED) {
			conn[idx] = i;
			conn[i] = idx;
			return i;
		}
	}
	return UNDEFINED;
}

int main(void)
{
	int fail, comp, aband;

	// Get input
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", num + i);
	}

	// printf("Numbers: ");
	// for (int i = 0; i < n; i++) {
	// 	printf("%d ", num[i]);
	// } printf("\n");

	// Get primes
	for (int i = 2; i < 1001; i++) {
		if (prime[i]) continue;
		for (int j = i * i; j < 2001; j += i) {
			prime[j] = 1;
		}
	}

	// Get graph
	for (int i = 0; i < n; i++) {
		mat[i][i] = 1;
		for (int j = i + 1; j < n; j++) {
			mat[i][j] = prime[num[i] + num[j]];
			mat[j][i] = mat[i][j];
		}
	}
	
	// Initialize connection
	for (int i = 0; i < n; i++) {
		conn[i] = UNDEFINED;
	}

	// Get fully connected
	fail = 0;
	for (int i = 0; i < n; i++) {
		if (conn[i] != UNDEFINED) continue;
		for(int j = 0; j < n; j++) visited[j] = 0;
		if (make_connection(i) == UNDEFINED) {
			fail = 1;
			break;
		}
	}
	if (fail) {
		printf("-1");
		return 0;
	}

	// Get answers
	for (int i = 1; i < n; i++) {
		if (mat[0][i]) continue;

		if (conn[0] == i) {
			ans[ans_num++] = num[i];
			continue;
		}

		aband = conn[0];
		comp = conn[i];

		conn[aband] = UNDEFINED;
		conn[comp] = UNDEFINED;
		conn[0] = i;
		conn[i] = 0;
		
		for (int j = 0; j < n; j++) {
			visited[j] = 0;
		}
		visited[0] = 1;
		visited[i] = 1;

		if (make_connection(aband) == UNDEFINED) {
			conn[0] = aband;
			conn[aband] = 0;
			conn[i] = comp;
			conn[comp] = i;
		} else {
			ans[ans_num++] = num[i];
		}
	}

	sort(ans, ans + ans_num);
	for (int i = 0; i < ans_num; i++) {
		printf("%d ", ans[i]);
	}

	return 0;
}