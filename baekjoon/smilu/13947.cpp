#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef pair<double, double> pdd;

double dist(pdd a, pdd b) {
  double dx = a.first - b.first;
  double dy = a.second - b.second;
  return sqrt(dx*dx + dy*dy);
}
double dist2(pdd a, pdd b) {
  double dx = a.first - b.first;
  double dy = a.second - b.second;
  return dx*dx + dy*dy;
}

int n;
char s[21];

bool all_t() {
  for (int i = 0; i < n; i++)
    if (s[i] != 'T') return false;
  return true;
}

double tc(int sz) {
  if (sz == 0) return 0;
  pdd top = make_pair(0.5, sqrt(3) / 2);
  pdd center = make_pair(0.5 + sz, 0.5);
  double r = 0.5;
  double c = dist(top, center);
  double ans = sqrt(dist2(top, center) - r*r);
  ans += (M_PI / 2 - acos(sz / c) - acos(r / c)) * r;
  return ans;
}

double ts(int sz) {
  if (sz == 0) return 0;
  pdd top = make_pair(0.5, sqrt(3) / 2);
  pdd corner = make_pair((double)sz, 1.0);
  return dist(top, corner) + 0.5;
}

int main(void)
{
  scanf("%d%s", &n, s);
  if (all_t()) {
    printf("%lf\n", (double)(2*n+1));
    return 0;
  }
  int l = 0, r = n - 1;

  while (s[l] == 'T') ++l;
  while (s[r] == 'T') --r;
  double ans = n - 1 + r - l;

  if (s[l] == 'C') {
    ans += tc(l);
  } else { // 'S'
    ans += ts(l);
  }
    
  if (s[r] == 'C') {
    ans += tc(n-1-r);
  } else {
    ans += ts(n-1-r);
  }

       if (s[  0] == 'T') ans += 1.5;
  else if (s[  0] == 'S') ans += 2.0;
  else if (s[  0] == 'C') ans += M_PI / 2;

       if (s[n-1] == 'T') ans += 1.5;
  else if (s[n-1] == 'S') ans += 2.0;
  else if (s[n-1] == 'C') ans += M_PI / 2;

  printf("%lf\n", ans);
}
