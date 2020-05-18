#include <bits/stdc++.h>
using namespace std;

int n, n2;
int w[20][20];

int ability(const vector<int> &grp) {
  int ret = 0;
  for (int i = 0; i < n2; i++) {
    for (int j = 0; j < n2; j++) {
      ret += w[grp[i]][grp[j]];
    }
  }
  return ret;
}

int main(void)
{
  scanf("%d", &n); n2 = n/2;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    scanf("%d", &w[i][j]);
  }
  vector<bool> comb(n, false);
  for (int i = n2; i < n; i++) comb[i] = true;
  int ret = 0x7fffffff;
  do {
    vector<int> t1, t2;
    for (int i = 0; i < n; i++) (comb[i]?t1:t2).push_back(i);
    assert(t1.size() == n2);
    assert(t2.size() == n2);
    int a1 = ability(t1);
    int a2 = ability(t2);
    ret = min(ret, abs(a1-a2));
  } while (next_permutation(comb.begin(), comb.end()));
  printf("%d\n", ret);
}
