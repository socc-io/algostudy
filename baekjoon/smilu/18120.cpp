#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Crop {
  double r;
  int value;
};

double get_r(int x, int y) {
  double x2 = (double)x; x2 *= x2;
  double y2 = (double)y; y2 *= y2;
  return sqrt(x2 + y2);
}

bool by_r(const Crop& a, const Crop& b) {
  return a.r < b.r;
}

int n, a;
Crop crops[100000];
double sum_wi[100000];
double sum_wi_ri[100000];

// p = sum{wi * (r - ri)} - a*r*r
// p = r*sum{wi} - sum{wi*ri} - a*r*r
// dp/dr = sum{wi} - 2*a*r = 0
// r = sum{wi} / (2a)
// max_p = sum^2{wi}/(2a) - sum{wi*ri} - a*(sum{wi}/2a)

int main(void)
{
  scanf("%d%d", &n, &a);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d%d", &x, &y, &crops[i].value);
    crops[i].r = get_r(x, y);
  }
  sort(crops, crops + n, by_r);

  sum_wi[0] = crops[0].value;
  sum_wi_ri[0] = crops[0].r * crops[0].value;
  for (int i = 1; i < n; i++) {
    sum_wi[i] = sum_wi[i-1] + crops[i].value;
    sum_wi_ri[i] = sum_wi_ri[i-1] + crops[i].r * crops[i].value;
  }
  
  double mp = 0;
  for (int i = 0; i < n; i++) {
    double r = sum_wi[i] / (2 * a);
    double p = r * sum_wi[i] - sum_wi_ri[i] - a*r*r;
    if (p > mp) mp = p;
  }
  printf("%lf", mp);
}

