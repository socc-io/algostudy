#include <cstdio>
#include <algorithm>
using namespace std;

int main(void)
{
  int v[3];
  scanf("%d%d%d", v, v+1, v+2);
  if (v[0] == v[1] && v[1] == v[2]) {
    printf("%d000\n", 10+v[0]); return 0;
  }
  if (v[0] == v[1]) {
    printf("%d00\n", 10+v[0]); return 0;
  }
  if (v[1] == v[2]) {
    printf("%d00\n", 10+v[1]); return 0;
  }
  if (v[0] == v[2]) {
    printf("%d00\n", 10+v[0]); return 0;
  }
  printf("%d00\n", max(v[0], max(v[1],v[2])));
}
