#include <iostream>

using namespace std;

struct v {
	int x, y;
	v(int x=0, int y=0): x(x), y(y) {}
};

int T;
v r[2], p[2], dp;

int coll_hori(int y, int l, int r)
{
	if(!dp.y) {
		if(y != p[0].y) return 0;
		int l2 = p[0].x, r2 = p[1].x;
		if(l2 > r2) swap(l2, r2);
		if(r2 < l) return 0;
		if(r2 == l) return 1;
		if(r2 <= r) return 10;
		if(l2 < r) return 10;
		if(l2 == r) return 1;
		return 0;
	}
	l *= dp.y; r *= dp.y;
	int x = dp.x*(y-p[1].y)+p[1].x*dp.y;
	if(p[0].x*dp.y > x || x > p[1].x*dp.y) return 0;
	if(l < x && x < r) return 2;
	if(x == l || x == r) return 1;
	return 0;
}
int coll_vert(int x, int l, int r)
{
	if(!dp.x) {
		if(x != p[0].x) return 0;
		int l2 = p[0].y, r2 = p[1].y;
		if(l2 > r2) swap(l2, r2);
		if(r2 < l) return 0;
		if(r2 == l) return 1;
		if(r2 <= r) return 10;
		if(l2 < r) return 10;
		if(l2 == r) return 1;
		return 0;
	}
	l *= dp.x; r *= dp.x;
	int y = dp.y*(x-p[1].x) + p[1].y*dp.x;
	if(p[0].y*dp.x > y || y > p[1].y*dp.x) return 0;
	if(l < y && y < r) return 2;
	if(x == l || x == r) return 1;
	return 0;
}

int main(void)
{
	for(scanf("%d", &T); T--;) {
		scanf("%d%d%d%d%d%d%d%d", &r[0].x, &r[0].y, &r[1].x, &r[1].y, &p[0].x, &p[0].y, &p[1].x, &p[1].y);
		dp = { p[0].x - p[1].x, p[0].y - p[1].y };
		int res = coll_hori(r[0].y, r[0].x, r[1].x) +
			coll_hori(r[1].y, r[0].x, r[1].x) +
			coll_vert(r[0].x, r[0].y, r[1].y) +
			coll_vert(r[1].x, r[0].y, r[1].y);
		printf("%d\n", res >= 10 ? 4 : res/2);
	}
}