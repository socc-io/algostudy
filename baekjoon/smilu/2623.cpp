#include <cstdio>
#include <vector>
#include <set>
using namespace std;

int n, m;
set<int> prevs[1001];
bool inans[1001];

int find_empty() {
  for (int i = 1; i <= n; i++) {
    if (inans[i]) continue;
    if (prevs[i].empty()) return i;
  }
  return -1;
}

void fill(int v) {
  for (int i = 1; i <= n; i++) {
    prevs[i].erase(v);
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int c; scanf("%d", &c);
    int prev_tmp;
    for (int j = 0; j < c; j++) {
      int tmp; scanf("%d", &tmp);
      if (j == 0) {
        prev_tmp = tmp;
        continue;
      }
      prevs[tmp].insert(prev_tmp);
      prev_tmp = tmp;
    }
  }
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    int ei = find_empty();
    if (ei == -1) {
      puts("0"); return 0;
    }
    fill(ei);
    ans.push_back(ei);
    inans[ei] = true;
  }
  for (int i = 0; i < ans.size(); i++) {
    printf("%d\n", ans[i]);
  }
}
