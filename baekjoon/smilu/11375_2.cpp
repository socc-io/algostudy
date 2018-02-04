
#include <iostream>
#include <cstring>

// #define DEBUG

using namespace std;

int n, m;
int p[1000][1000];
int pl[1000];
int fm[1000];
int bm[1000];

int match(int u)
{
	if(pl[u] == 1) return 0;
	pl[u] = 1;
	for(int i=0; i<m; ++i) {
		if(p[u][i] == 0) continue;
		if(bm[i] == -1 || match(bm[i]) == 1) {
			fm[u] = i;
			bm[i] = u;
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	scanf("%d%d", &n, &m);

	/*
	 * Initialize global
	 */
	for(int i=0; i<n; ++i) {
		fm[i] = -1;
	}
	for(int i=0; i<m; ++i) {
		bm[i] = -1;
	}
	memset(p, 0, sizeof(p));

	/*
     * Get input
     */
	for(int i=0; i<n; ++i) {
		int pn; scanf("%d", &pn);
		for(int j=0; j<pn; ++j) {
			int w; scanf("%d", &w);
			p[i][w-1] = 1;
		}
	}

	/*
	 * Find matching
	 */
	int ans = 0;
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) pl[j] = 0;
		ans += match(i);
	}

#ifdef DEBUG
		printf("match: ");
		for(int i=0; i<n; ++i) {
			printf("%d ", fm[i] + 1);
		}
		puts("");
#endif

	printf("%d", ans);
}