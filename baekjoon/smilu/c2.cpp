#include <bits/stdc++.h>
using namespace std;

const double pi = 3.14159265358979323846264338327950288;

void solve()
{
  int n; scanf("%d", &n);
  n <<= 1;
  double t = pi/2 - pi/n;
  double k;
  k = sqrt(1/(cos(t)*cos(t)) - 3.0/4.0);
  printf("%lf\n", k);
  k = tan(t);
  printf("%lf\n", k);
  k = 1/cos(t);
  printf("%lf\n", k);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
