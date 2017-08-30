#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long lld;
using namespace std;

lld mabs(lld k) {
	if(k >= 0) return k;
	return -k;
}

struct Vertex {
	lld x, y;
	Vertex(lld x=0, lld y=0): x(x), y(y) {}
	lld dist2(const Vertex &B) {
		lld dx = x - B.x, dy = y - B.y;
		return (dx*dx + dy*dy);
	}
	lld taxi_dist(const Vertex &B) {
		return mabs(x - B.x) + mabs(y - B.y);
	}
	Vertex operator-(const Vertex &B) {
		return Vertex(x - B.x, y - B.y);
	}
};

int T, N;
Vertex coords[200000];

lld ccw(const Vertex &p1, const Vertex &p2, const Vertex &p3)
{
	return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
}

int main(void)
{
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d", &N);
		for(int i = 0; i < N; ++i) {
			scanf("%lld%lld", &coords[i].x, &coords[i].y);
		}
		for(int i = 1; i < N; ++i) {
			if(coords[0].y > coords[i].y) {
				swap(coords[0], coords[i]);
			}
		}
		sort(coords + 1, coords + N, [](const Vertex &A, const Vertex &B) {
			lld k = ccw(coords[0], A, B);
			if(k) return k > 0;
			return coords[0].taxi_dist(A) < coords[0].taxi_dist(B);
		});
		vector<Vertex> S = { coords[0] };
		S.reserve(N); 
		S.push_back(coords[0]);
		for(int i = 1; i < N; ++i) {
			while(S.size() > 1 && ccw( S[S.size()-2], S[S.size()-1], coords[i] ) <= 0) {
				S.pop_back();
			}
			S.push_back(coords[i]);
		}
		lld max_dist = S[0].dist2(S[1]);
		int l = 0, r = 1;
		for(int i = 0; i < N; ++i) {
			for(int j = i+1; j < N; ++j) {
				lld lc_dist = S[i].dist2(S[j]);
				if(lc_dist > max_dist) {
					max_dist = lc_dist;
					l = i;
					r = j;
				}
			}
		}
		int j = 1, slen = S.size();
	    lld ans = 0; Vertex p, q;
	    for (int i=0;i<slen;i++){
	        int ni = (i+1) % slen;
	        for (;;){
	            int nj = (j+1) % slen;
	            lld v = ccw(Vertex(0, 0), S[ni] - S[i], S[nj] - S[j]);
	            if (v > 0) j = nj;
	            else break;
	        }
	        lld v = S[i].dist2(S[j]);
	        if (ans < v)
	            ans = v, p = S[i], q = S[j];
	    }
		printf("%lld %lld %lld %lld\n", p.x, p.y, q.x, q.y);
	}
}