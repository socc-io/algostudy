/*
 * author: smilu97
 * description:
 * 	problem solving of https://www.acmicpc.net/problem/1017
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int N, hN;
vector<int> a, b, ans;
vector<int> adj[25];
bool visit[25];
bool prime[2001];
int a_match[25];
int b_match[25];

bool match(int ai)
{
	if (visit[ai]) return 0;
	visit[ai] = 1;
	for (int bi: adj[ai]) {
		if (b_match[bi] == -1 || match(b_match[bi])) {
			a_match[ai] = bi;
			b_match[bi] = ai;
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	for (int i = 2; i < 2001; i++) prime[i] = 1;
	for (int i = 2; i < 50; i++) {
		if (!prime[i]) continue;
		for (int j = (i << 1); j < 2001; j += i) {
			prime[j] = 0;
		}
	}

	scanf("%d", &N);
	hN = N >> 1;
	bool odd_first;
	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		if (i == 0) odd_first = tmp & 1;
		((tmp & 1) ? a : b).push_back(tmp);
	}
	if (a.size() != b.size()) {
		puts("-1");
		return 0;
	}
	if (!odd_first) swap(a, b);

	for (int i = 0; i < hN; i++) {
		for (int j = 0; j < hN; j++) {
			if (prime[a[i] + b[j]]) {
				adj[i].push_back(j);
			}
		}
	}

	for (int bi: adj[0]) {
		memset(a_match, -1, sizeof(a_match));
		memset(b_match, -1, sizeof(b_match));

		a_match[0] = bi;
		b_match[bi] = 0;

		bool fail = 0;
		for (int i = 1; i < hN; i++) {
			memset(visit, 0, sizeof(visit));
			visit[0] = 1;
			if (!match(i)) {
				fail = 1;
				break;
			}
		}

		if (!fail) ans.push_back(b[bi]);
	}
	if (ans.empty()) puts("-1");
	else {
		sort(ans.begin(), ans.end());
		for(int r: ans) {
			printf("%d ", r);
		}
	}

	return 0;
}