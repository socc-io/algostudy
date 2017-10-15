#include<iostream>
#include<algorithm>
using namespace std;

struct edge {
	int v[2];
	int w;
	void input() {
		scanf("%d%d%d", v, v+1, &w);
		--v[0];
		--v[1];
	}
	bool operator<(const edge& b) const {
		return w < b.w;
	}
} edges[100000];

int n,m;
int grp_idx;
int grp[100000];
int lnk[100000];

int main()
{
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; ++i) {
		edges[i].input();
	}
	sort(edges, edges+m);
	int ans = 0;
	for(int i=0; i<n; ++i) {
		grp[i] = -1;
		lnk[i] = -1;
	}
	for(int i=0; i<m; ++i) {
		int ag = grp[edges[i].v[0]];
		int bg = grp[edges[i].v[1]];
		while(lnk[ag] != -1 && ag != -1) ag = lnk[ag];
		while(lnk[bg] != -1 && bg != -1) bg = lnk[bg];
		if(ag == -1 || bg == -1) {
			ans += edges[i].w;
			if(ag == -1 && bg == -1) {
				grp[edges[i].v[0]] = grp_idx;
				grp[edges[i].v[1]] = grp_idx++;
			} else {
				int g = ag;
				if(g == -1) g = bg;
				grp[edges[i].v[0]] = g;
				grp[edges[i].v[1]] = g;
			}
		} else if(ag != bg) {
			if(ag > bg) swap(ag, bg);
			lnk[bg] = ag;
			ans += edges[i].w;
		} else {
			continue;
		}
	}
	printf("%d", ans);
}