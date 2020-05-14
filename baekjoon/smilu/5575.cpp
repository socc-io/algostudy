#include <cstdio>
int ct() {
  int a, b, c; scanf("%d%d%d", &a, &b, &c);
  return a*3600+b*60+c;
}
void pt(int t) {
  t *= -1;
  printf("%d %d %d\n", t/3600, t/60%60, t%60);
}
int main(void)
{
  pt(ct()-ct());
  pt(ct()-ct());
  pt(ct()-ct());
}