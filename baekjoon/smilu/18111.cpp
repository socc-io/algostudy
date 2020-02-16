#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, B;
int NM;
int maxh;
int hs[250000];

int get_cost(int h)
{
  int cost = 0;
  for (int i = 0; i < NM; i++) {
    int diff = hs[i] - h;
    if (diff > 0) cost += 2 * diff;
    else cost -= diff;
  }
  return cost;
}

int main(void)
{
  scanf("%d%d%d", &N, &M, &B);
  NM = N * M;
  for (int i = 0; i < NM; i++) {
    scanf("%d", hs+i);
  }
  sort(hs, hs+NM);

  maxh = B;
  for (int i = 0; i < NM; i++) {
    maxh += hs[i];
  }
  maxh /= NM;
  maxh = maxh > 256 ? 256 : maxh;

  int mincost = -1;
  int minh = -1;
  for (int h = hs[0]; h <= maxh; h++) {
    int cost = get_cost(h);
    if (cost <= mincost || minh == -1) {
      mincost = cost;
      minh = h;
    }
  }

  printf("%d %d", mincost, minh);
}