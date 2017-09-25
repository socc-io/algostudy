#include<iostream>
#include<set>
#include<algorithm>
#include<cmath>
using namespace std;

#define INF 0x7FFFFFFF
#define BRUTAL_THRESHOLD 1

struct point {
    int x, y;
    point() {}
    point(int x, int y):x(x),y(y) {}
    bool operator<(const point &o)const{
        if(y == o.y) return x < o.x;
        return y < o.y;
    }
    int l2(const point &b) {
        int dx = x-b.x;
        int dy = y-b.y;
        return dx*dx+dy*dy;
    }
};

int n;
point p[100000];

int main(void)
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d%d", &(p[i].x), &(p[i].y));
    }
    sort(p, p+n, [](const point &a, const point &b) {
        return a.x < b.x;
    });
    set<point> cand = {p[0], p[1]};
    int d = p[0].l2(p[1]);
    int start = 0;
    for(int i=2; i<n; ++i) {
        point now = p[i];
        while(start < i) {
            point left = p[start];
            int dx = now.x - left.x;
            if(dx*dx > d) {
                cand.erase(left);
                ++start;
            } else break;
        }
        int sd = (int)sqrt(d)+1;
        auto lo = cand.lower_bound(point(0, now.y-sd));
        auto uo = cand.upper_bound(point(0, now.y+sd));
        for(auto it = lo; it != uo; ++it) {
            int nd = now.l2(*it);
            if(nd < d) d = nd;
        }
        cand.insert(now);
    }
    printf("%d", d);
}
