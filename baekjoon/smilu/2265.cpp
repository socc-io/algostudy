#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN (1000)
#define HMAXN (MAXN/2)

struct Group {
	int point;
	int val;
} group[MAXN];

struct Person {
	vector<pair<int,int>> conn;
	Group * group;
	int val;
} person[MAXN];

pair<int,int> dp[MAXN][MAXN];

void make_group(Person * p, Group * g, int val)
{
	if(p->group != NULL) return;
	p->group = g;
	p->val = val;
	g->point += val;
	for(auto it = p->conn.begin(); it != p->conn.end(); ++it)
		make_group(person + it->first, g, val * it->second);
}

int main(void)
{
	char buf[4];
	int qn, p1, p2, group_num = 0, gp;
	scanf("%d%d%d", &qn, &p1, &p2);
	int n = p1 + p2, pd = p1 - p2 + HMAXN;
	for(int i=0; i<qn; ++i) {
		int a, b, w;
		scanf("%d%d%s", &a, &b, buf);
		--a; --b;
		w = strcmp(buf, "yes") == 0 ? 1 : -1;
		person[a].conn.push_back({b, w});
		person[b].conn.push_back({a, w});
	}
	for(int i=0; i<n; ++i) if(person[i].group == NULL)
		make_group(person + i, group + group_num++, 1);
	dp[0][HMAXN] = {1, 0};
	for(int i=1; i<=group_num; ++i) for(int j=0; j<MAXN; ++j) {
		if(dp[i-1][j].first == 0) continue;
		gp = group[i-1].point;
		dp[i][j+gp].first += dp[i-1][j].first;
		dp[i][j+gp].second = j;
		dp[i][j-gp].first += dp[i-1][j].first;
		dp[i][j-gp].second = j;
	}
	if(dp[group_num][pd].first == 1) {
		for(int i=group_num; i>=0; --i, pd = dp[i][pd].second)
			group[i-1].val = (dp[i][pd].second + group[i-1].point == pd) ? 1 : -1;
		for(int i=0; i<n; ++i) if(person[i].group->val * person[i].val == 1)
			printf("%d ", i+1);
	} else printf("NO");
}