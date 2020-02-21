#include <cstdio>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFF0

int abs(int v) { return v >= 0 ? v : -v; }

int n;
int arr[100000];

int main(void)
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  int min = INF;
  int a, b;
  for (int i = 0; i < n; i++) {
    int v = arr[i];
    int *lo = lower_bound(arr, arr+n, -v);
    for (int j = -1; j <= 1; j++) {
      int *p = lo + j;
      if (p == arr + i) continue;
      if (p < arr || p >= arr + n) continue;
      int w = *p;
      int d = abs(v + w);
      // printf("(%d, %d) => %d\n", v, w, d);
      if (d < min) {
        min = d;
        a = v;
        b = w;
      }
    }
    if (lo == arr + i) ++lo;
  }
  printf("%d %d", a, b);
}