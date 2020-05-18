#include <bits/stdc++.h>
using namespace std;

const double pi = 3.14159265358979323846264338327950288;

void solve()
{
  int n; scanf("%d", &n);
  n <<= 1;
  double k = tan(pi/2 - pi/n);
  printf("%lf\n", k);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
