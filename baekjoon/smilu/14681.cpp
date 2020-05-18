#include <cstdio>

const int v[2][2] = {{3,2},{4,1}};

int main(void)
{
  int x, y; scanf("%d%d", &x, &y);
  printf("%d\n", v[x>0][y>0]);
}
