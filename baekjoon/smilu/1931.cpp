#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long llu;

llu zip(int a, int b) {
  return (llu)a << 32 | b;
}
int left(llu a) { return a >> 32; }
int right(llu a) { return a & 0xFFFFFFFF; }

int n;
llu is[100000];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int start, end;
    scanf("%d%d", &start, &end);
    is[i] = zip(end, start);
  }
  sort(is, is + n);

  int t = -1;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    int start = right(is[i]);
    if (t <= start) {
      cnt++;
      int end = left(is[i]);
      t = end;
      // printf("did: %d, %d\n", start, end);
      // ioioioioioioioioioi
      // 00121234345
    }
  }

  printf("%d", cnt);
}