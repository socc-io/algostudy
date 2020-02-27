#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

#define F_INF 9999999.0f

struct point {
  double x, y;
};

int n;
point points[100];

double l2_distance(point a, point b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

double prim_algo(int start) {
  vector<bool> s(n, false);
  vector<double> dist(n, F_INF); // distances

  dist[start] = 0.0f;

  double sum = 0;

  while (1) {
    /*
    Find nearest point from points which is not included in set s
    */
    int next = -1;
    double next_dist = F_INF;
    for (int i = 0; i < n; i++) {
      if (s[i]) continue;
      if (dist[i] < next_dist) {
        next_dist = dist[i];
        next = i;
      }
    }
    if (next == -1) break;

    /*
    Include point[next] in set s, and sum dist.
    */
    sum += next_dist;
    s[next] = true;

    /*
    Update distance vector
    */
    for (int i = 0; i < n; i++) {
      if (s[i]) continue;
      double tmp_dist = l2_distance(points[next], points[i]);
      if (tmp_dist < dist[i]) {
        dist[i] = tmp_dist;
      }
    }
  }

  return sum;
}

int main(void)
{
  cin.tie(NULL);  // 넘나 귀찮은 것
  ios::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
  }
  double ans = prim_algo(0);
  cout << fixed;
  cout.precision(8);
  cout << ans << '\n';
}
