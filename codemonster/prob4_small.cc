#include<iostream>
#include<algorithm>
using namespace std;

typedef long long lld;

struct point {
	lld x, y;
	lld k() { return x+y; }
	point(){}
	point(lld x, lld y):x(x),y(y) {}
	void input() { scanf("%lld%lld", &x, &y); }
};

int n, k;
point poly[1000];
point tri[3];

int t_inside[3];
int p_inside[1000];

#define APARENT 16
#define BPARENT 8
#define MIDPOINT 4
#define MANYPOINT 2
#define ONEPOINT 1

bool mmid(lld a, lld b, lld c) { if(a>b) swap(a, b); return a<c && c<b; }
inline lld ccw(point a, point b, point c) {
	lld val = (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
	if(val < 0) return -1;
	else if(val > 0) return 1;
	else return 0;
}

int get_coll(point a, point b, point c, point d)
{
	if(ccw(a, b, c) == 0 && ccw(a, b, d) == 0) {
		lld ak = a.k(), bk = b.k(), ck = c.k(), dk = d.k();
		if(mmid(ak, bk, ck) || mmid(ak, bk, dk)) return MANYPOINT;
		if(ak == ck || bk == ck || ak == dk || bk == dk) return ONEPOINT + APARENT + BPARENT;
		return 0;
	}
	lld c1 = ccw(a, b, c)*ccw(a, b, d);
	lld c2 = ccw(c, d, a)*ccw(c, d, b);
	if(c1 <= 0 && c2 <= 0) {
		if(c1 == 0 || c2 == 0) return ONEPOINT + (c1 == 0 ? APARENT : 0) + (c2 == 0 ? BPARENT : 0);
		else return MIDPOINT;
	}
	return 0;
}

bool get_on(point a, point b, point c)
{
	if(ccw(a, b, c) != 0) return false;
	lld ak = a.k(), bk = b.k(), ck = c.k();
	if(ak > bk) swap(ak, bk);
	return ak <= ck && ck <= bk;
}

int get_inside(point a, point *p, int ps)
{
	int ans = -1;
	for(int i=0; i<ps; ++i) {
		if(get_on(p[i], p[(i+1)%ps], a)) return 0;
		int coll = get_coll(p[i], p[(i+1)%ps], point(20005, a.y), a);
		if(coll & (MIDPOINT | ONEPOINT)) {
			ans *= -1;
		}
	}
	return ans;
}

inline bool chk_inside()
{
 	for(int i=0; i<3; ++i) if(t_inside[i] < 0) return false;
 	for(int i=0; i<n; ++i) if(p_inside[i] > 0) return false;
 	return true;
}
inline bool chk_outside()
{
	for(int i=0; i<3; ++i) if(t_inside[i] >= 0) return false;
	for(int i=0; i<n; ++i) if(p_inside[i] >= 0) return false;
	return true;
}

void do_task()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		poly[i].input();
	}
	scanf("%d", &k);
	for(int kidx=0; kidx<k; ++kidx) {
		for(int i=0; i<3; ++i) tri[i].input();
		// printf("(%d, %d, %d) ", inside[0], inside[1], inside[2]);
		for(int i=0; i<3; ++i) t_inside[i] = get_inside(tri[i], poly, n);
		for(int i=0; i<n; ++i) p_inside[i] = get_inside(poly[i], tri, 3);
		if(chk_inside()) printf("1 ");
		else if(chk_outside()) printf("2 ");
		else printf("4 ");
	}
	puts("");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--) do_task();
}
