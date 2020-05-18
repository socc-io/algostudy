#include <cstdio>
#include <algorithm>
using namespace std;

int main(void)
{
  int n, s; scanf("%d%d", &n, &s); 
  if (2*n <= s) {
    puts("YES");
    for (int i = 1; i < n; i++) printf("2 ");
    printf("%d\n", s-2*(n-1));
    puts("1");
  } else {
    puts("NO");
  }
}