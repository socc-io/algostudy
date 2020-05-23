#include <bits/stdc++.h>
using namespace std;

int n, m;
bool tile[11][11];

vector<int> adj[30];
bool lck[30];
int match[30];

bool try_match(int i) {
  if (lck[i]) return false;
  lck[i] = true;
  for (int j: adj[i]) {
    if (match[j] == -1 || try_match(match[j])) {
      match[j] = i;
      lck[i] = false;
      return true;
    }
  }
  lck[i] = false;
  return false;
}

int main(void)
{
  scanf("%d", &n); m = (n<<1)-1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp; scanf("%d", &tmp);
      tile[i][j] = (bool)tmp;
    }
  }
  for (int i = 0; i < m; i++) { // i = x+y
    for (int x = 0; x <= i; x++) {
      int y = i - x;
      if (x < 0 || x >= n) continue;
      if (y < 0 || y >= n) continue;
      if (!tile[x][y]) continue;
      int j = (y-x) + (n-1);
      adj[i].push_back(j);
    }
  }
  memset(match, 0xff, sizeof(match));
  int ans = 0;
  for (int i = 0; i < m; i++) ans += try_match(i);
  printf("%d\n", ans);
}
