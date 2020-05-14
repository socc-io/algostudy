#include <cstdio>

int main(void)
{
  while (1) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c); 
    if (a == 0 && b == 0 && c == 0) break;
    c -= a;
    if (b*c < 0) { puts("X"); continue; }
    if (b<0) b*=-1, c*=-1;
    if (c%b != 0) { puts("X"); continue; }
    printf("%d\n", c/b+1);  
  }
}