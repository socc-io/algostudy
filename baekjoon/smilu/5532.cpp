#include <cstdio>
#include <algorithm>
using namespace std;
int main(void)
{
  int l, a, b, c, d;
  scanf("%d%d%d%d%d", &l,&a,&b,&c,&d);
  printf("%d\n", l-max((a+c-1)/c, (b+d-1)/d));
}