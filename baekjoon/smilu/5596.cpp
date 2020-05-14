#include <cstdio>
#include <algorithm>
using namespace std;
int scan() {
  int v = 0;
  for (int i = 0; i < 4; i++) {
    int t; scanf("%d", &t); v += t;
  }
  return v;
}
int main(void)
{
  printf("%d\n", max(scan(),scan()));
}