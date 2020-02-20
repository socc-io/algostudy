#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct position {
  int x;
  int y;
};

int abs(int v) { return v > 0 ? v : -v; }
int l2(position* a, position* b) {
  return abs(a->x - b->x) + abs(a->y - b->y);
}

int n, m;
position hs[100];
int hsn;
position cs[13];
int csn;
int dm[100][13];

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp; scanf("%d", &tmp);
      if (tmp == 1) {
        hs[hsn].x = i;
        hs[hsn].y = j;
        ++hsn;
      } else if (tmp == 2) {
        cs[csn].x = i;
        cs[csn].y = j;
        ++csn;
      }
    }
  }

  for (int i = 0; i < hsn; i++) {
    for (int j = 0; j < csn; j++) {
      dm[i][j] = l2(hs+i, cs+j);
      // printf("%d ", dm[i][j]);
    }
    // puts("");
  }

  vector<bool> perm;
  int mmin = 0x7FFFFFFF;
  for (int i = 0; i < csn - m; i++) perm.push_back(false);
  for (int i = 0; i < m; i++) perm.push_back(true);
  do {
    // printf("try: ");
    // for (int i = 0; i < csn; i++) printf("%d ", perm[i] ? 1 : 0);
    // puts("");
    int sum = 0;
    for (int i = 0; i < hsn; i++) {
      int min = 0x7FFFFFFF;
      for (int j = 0; j < csn; j++) {
        if (!perm[j]) continue;
        if (dm[i][j] < min) min = dm[i][j];
      }
      sum += min;
    }
    // printf("\t%d\n", sum);
    if (sum < mmin) mmin = sum;
  } while (next_permutation(perm.begin(), perm.end()));
  
  printf("%d", mmin);
}