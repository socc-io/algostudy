#include<iostream>
#include<algorithm>
using namespace std;

typedef long long lld;

struct point {
	lld x, y;
	lld k() { return x+y; }
	point(){}
	point(lld x, lld y):x(x),y(y) {}
	void input() { scanf("%lld%lld", &x, &y); x *= 2; y *= 2; }
};

int n, k;
point poly[1000];
point tri[3];
int inside[3];
int t_inside[3];

#define APARENT 16
#define BPARENT 8
#define MIDPOINT 4
#define MANYPOINT 2
#define ONEPOINT 1

bool mmid(lld a, lld b, lld c) { if(a>b) swap(a, b); return a<c && c<b; }
bool mid(lld a, lld b, lld c) { if(a>b) swap(a, b); return a<=c && c<=b; }
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

int get_inside(point a)
{
	int ans = -1;
	for(int i=0; i<n; ++i) {
		if(get_on(poly[i], poly[(i+1)%n], a)) return 0;
		if(get_coll(poly[i], poly[(i+1)%n], point(a.x, 20005), a) & (MIDPOINT | ONEPOINT)) ans *= -1;
	}
	return ans;
}

bool chk_including()
{
	for(int i=0; i<n; ++i) {
		int val = -1;
		for(int j=0; j<3; ++j) {
			if(get_on(tri[j], tri[(j+1)%3], poly[i])) { val = 0; break; }
			if(get_coll(tri[j], tri[(j+1)%3], point(poly[i].x, 20005), poly[i]) & (MIDPOINT | ONEPOINT)) val *= -1;
		}
		if(val < 0) return false;
	}
	return true;
}

int get_line_inside(point a, point b, point c, int aidx)
{
	int ai = t_inside[aidx], bi = t_inside[(aidx+1)%3];
	if(ai * bi == -1) return 2;
	bool many = false;
	for(int i=0; i<n; ++i) {
		point p = poly[i], q = poly[(i+1)%n], r = poly[(i+2)%n];
		int coll = get_coll(a, b, p, q);
		if(coll & MIDPOINT) return 2;
		if((coll & ONEPOINT)) {
			if((coll & APARENT) > 0 && (coll & BPARENT) == 0) {
				if(ccw(a, b, q) == 0 && ccw(a, b, p)*ccw(a, b, r) < 0) return 2;
			}
			else if((coll & APARENT) == 0 && (coll & BPARENT) > 0) {
				if(ccw(p, q, b) == 0 && ccw(p, q, a)*ccw(p, q, c) < 0) return 2;
			}
			else if((coll & APARENT) > 0 && (coll & BPARENT) > 0 && ccw(a, b, q) == 0) {
				int c1 = ccw(a, b, p)*ccw(a, b, r);
				int c2 = ccw(p, q, a)*ccw(p, q, c);
				if(c1 < 0 && c2 < 0) return 2;
			}
		}
		if((coll & MANYPOINT)) many = true;
	}
	if(ai == -1 || bi == -1) return -1;
	if(ai ==  1 || bi ==  1) return 1;
	point m = point((a.x+b.x)/2, (a.y+b.y)/2);
	return get_inside(m);
}

inline bool chk_inside() {
	for(int i=0; i<3; ++i) if(inside[i] < 0) return false;
	return true;
}
inline bool chk_outside() {
	for(int i=0; i<3; ++i) if(inside[i] > 0) return false;
	for(int i=0; i<3; ++i) if(t_inside[i] >= 0) return false;
	return true;
}
inline bool chk_crossing() {
	bool ou = false, in = false;
	for(int i=0; i<3; ++i) if(inside[i] == 2) return true;
	for(int i=0; i<3; ++i) if(inside[i] == -1) { ou = true; break; }
	for(int i=0; i<3; ++i) if(inside[i] == 1)  { in = true; break; }
	if(ou && in) return true;
	return false;
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
		for(int i=0; i<3; ++i) t_inside[i] = get_inside(tri[i]);
		for(int i=0; i<3; ++i) {
			inside[i] = get_line_inside(tri[i], tri[(i+1)%3], tri[(i+2)%3], i);
		}
		// printf("(%d, %d, %d) ", inside[0], inside[1], inside[2]);
		if(chk_including()) printf("4 ");
		else if(chk_crossing()) printf("4 "); 
		else if(chk_inside()) printf("1 ");
		else if(chk_outside()) printf("2 ");
		else printf("3 ");
	}
	puts("");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--) do_task();
}
