#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;


typedef double coord_t;
typedef double coord2_t;

struct Point {
	coord_t x, y;
	
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};


coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (long)(A.x - O.x) * (B.y - O.y) - (long)(A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P)
{
	int n = (int)P.size();
	int k = 0;
	vector<Point> H(2*n);
	
	sort(P.begin(), P.end());
	
	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
	
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--;
		H[k++] = P[i];
	}
	
	H.resize(k);
	return H;
}


void func() {
	int n;
	scanf("%d", &n);
	
	vector<Point> VP;
	vector<Point> hull;
	
	for (int i=0; i<n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		
		Point p;
		p.x = (coord_t) x;
		p.y = (coord_t) y;
		
		VP.push_back(p);
	}
	
	double maxd = 0;
	tuple<int, int, int, int> ret;
	
	hull = convex_hull(VP);
	
	//double idx = 1;
	
	for (int i=0; i<hull.size(); i++) {
		double tmp = 0;
		
		for (int j=i+1; j<hull.size(); j++) {
			if (i == j) continue;
			
			double d = sqrt( pow(hull[i].x - hull[j].x, 2) + pow(hull[i].y - hull[j].y, 2) );
			if (maxd < d) {
				maxd = d;
				ret = make_tuple(hull[i].x, hull[i].y, hull[j].x, hull[j].y);
				
			}else if (tmp > d)
				break;
			
			
			tmp = d;
		}
	}
	int a,b,c,d;
	tie(a,b,c,d) = ret;
	
	printf("%d %d %d %d\n", a, b, c, d);
}