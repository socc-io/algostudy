#include<iostream>
using namespace std;

struct Quest {
	int x, y, r;
	void input() { scanf("%d%d%d", &x, &y, &r); }
};

int n;
Quest q[100];
int ans;
bool visit[1001][1001];

void travel(int x, int y) {
	if(x > 1000) x = 1000;
	if(y > 1000) y = 1000;
	// prevent duplication
	if(visit[x][y]) return;
	visit[x][y] = true;

	int rs = 0;
	int cnt = 0;
	for(int i=0; i<n; ++i) {
		if(q[i].x > x && q[i].y > y) continue;
		rs += q[i].r;
		++cnt;
	}
	if(cnt > ans) ans = cnt;
	int c = rs - x - y + 2;
	for(int i=0; i<=c; ++i) {
		travel(x+i, y+c-i);
	}
}

int main()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) q[i].input();
	travel(1, 1);
	printf("%d", ans);
}