#include <cstdio>
#include <tuple>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef tuple<int,int,int> t_edge;

int n, m;
t_edge edges[1000000];
int grp[100000];
int p_grp[100000];

int find_root(int g) {
  if (p_grp[g] == g) return g;
  int up = find_root(p_grp[g]);
  p_grp[g] = up;
  return up;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int from, to, weight;
    scanf("%d%d%d", &from, &to, &weight);
    edges[i] = make_tuple(weight, from-1, to-1);
  }
  sort(edges, edges+m);

  for (int i = 0; i < n; i++) {
    grp[i] = i;
    p_grp[i] = i;
  }

  int cnt_select = 0;
  int sum_w = 0;
  int max_w = 0;
  for (int i = 0; i < m; i++) {
    int w = get<0>(edges[i]);
    int l = get<1>(edges[i]);
    int r = get<2>(edges[i]);
    int rl = find_root(l), rr = find_root(r);
    if (rl == rr) continue;
    p_grp[rr] = rl;
    sum_w += w;
    if (w > max_w) max_w = w;
    cnt_select++;
    // printf("select w: %d:, l: %d, r: %d\n", w, l, r);
    if (cnt_select >= n-1) break;
  }

  printf("%d", sum_w - max_w);
}