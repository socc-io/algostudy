#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int ps[1000];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &ps[i]);
  }
  sort(ps, ps + n);

  int time = 0;
  int prev = 0;
  for (int i = 0; i < n; i++) {
    prev += ps[i];
    time += prev;
  }

  printf("%d", time);
}