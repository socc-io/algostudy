#include <bits/stdc++.h>
using namespace std;

int n, m;
int jmp[101];
int vs[101];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n+m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		jmp[a] = b;
	}
	
	queue< pair<int, int> > q;
	q.push({1, 0});
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		int nd = cur.second + 1;
		int mi = min(cur.first + 6, 100);
		for (int i = cur.first + 1; i <= mi; i++) {
			int v = i;
			while (jmp[v]) v = jmp[v];
			if (vs[v]) continue;
			vs[v] = 1;
			q.push({v, nd});
			if (v == 100) {
				printf("%d\n", nd);
				return 0;
			}
		}
	}
}
