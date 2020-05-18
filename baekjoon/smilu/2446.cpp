#include <cstdio>

void chars(char ch, int n) { for (int i = 0; i < n; i++) putchar(ch); }
void line(int n, int i) { chars(' ', n-i); chars('*', i*2-1); puts(""); }
int main(void)
{
  int n; scanf("%d", &n);
  for (int i = n; i >= 1; i--) line(n, i);
  for (int i = 2; i <= n; i++) line(n, i);
}
