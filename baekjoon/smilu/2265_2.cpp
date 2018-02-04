
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int qn, an, en, n, dn, gn;
vector<pair<int,int>> d[600];
pair<int,int> dep[600];
vector<int> group;
int point;
pair<int,int> dp[600][1200];

int visit(int pos, int base, int val)
{
	dep[pos] = {base, val};
	point += val;
	for(auto it = d[pos].begin(); it != d[pos].end(); ++it) {
		int nval = val * it->second;
		if(dep[it->first].first == base) {
			if(dep[it->first].second != nval) {
				return -1;
			}
			continue;
		}
		if(visit(it->first, base, nval) == -1) {
			return -1;
		}
	}
	return 0;
}

int main(void)
{
	char buf[1000];
	scanf("%d%d%d", &qn, &an, &en);
	n = an + en;
	dn = an - en;
	for(int i=0; i<qn; ++i) {
		int from, to;
		scanf("%d%d%s", &from, &to, buf);
		--from; --to;
		int w = strcmp(buf, "yes") == 0 ? 1 : -1;
		d[from].push_back({to,   w});
		d[to]  .push_back({from, w});
	}
	for(int i=0; i<n; ++i) {
		dep[i] = {-1, 1};
	}
	for(int i=0; i<n; ++i) {
		if(dep[i].first == -1) {
			point = 0;
			if(visit(i, group.size(), 1) == -1 || point == 0) {
				puts("NO");
				return 0;
			}
			group.push_back(point);
		}
	}
	gn = group.size();
	dp[0][600+group[0]] = {1, 600};
	dp[0][600-group[0]] = {1, 600};
	for(int i=1; i<gn; ++i) {
		int gp = group[i];
		for(int j=0; j<1200; ++j) {
			if(dp[i-1][j].first == 0) continue;
			dp[i][j+gp].first += dp[i-1][j].first;
			dp[i][j+gp].second = j;
			dp[i][j-gp].first += dp[i-1][j].first;
			dp[i][j-gp].second = j;
		}
	}
	vector<int> gs(gn, 0);
	if(dp[gn-1][600+dn].first == 1) {
		int cur = 600 + dn;
		for(int i=gn-1; i>=0; --i) {
			if(dp[i][cur].second + group[i] == cur) {
				gs[i] = 1;
			} else {
				gs[i] = -1;
			}
			cur = dp[i][cur].second;
		}
		for(int i=0; i<n; ++i) {
			if(gs[dep[i].first] * dep[i].second == 1) {
				printf("%d ", i + 1);
			}
		}
	} else {
		puts("NO");
	}
	return 0;
}