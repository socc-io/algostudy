#include <cstdio>
int main() {
  int n; scanf("%d", &n);
  printf("%d", (n/2+1)*(n/2+1+(n&1)));
}