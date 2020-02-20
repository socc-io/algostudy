#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

const int dd[4][2] = {
  {-1,0},{1,0},{0,1},{0,-1},
};

int n, m;
char tile[8][8];

int safearea() {
  vector<vector<bool>> fill(n, vector<bool>(m, 0));
  queue<pii> q;
  for (int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if (tile[i][j] != 2) continue;
      fill[i][j] = true;
      q.push(make_pair(i, j));
    }
  }
  while(!q.empty()) {
    pii u = q.front(); q.pop();
    for (int di = 0; di < 4; di++) {
      int nx = u.first + dd[di][0];
      int ny = u.second + dd[di][1];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if (tile[nx][ny] == 1) continue;
      if (fill[nx][ny]) continue;
      fill[nx][ny] = true;
      q.push(make_pair(nx, ny));
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if (tile[i][j] != 0) continue;
      if (fill[i][j]) continue;
      ++cnt;
    }
  }
  return cnt;
}

int main(void)
{
  vector<pii> blanks;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int tmp; scanf("%d", &tmp);
      tile[i][j] = tmp;
      if (tmp == 0) blanks.push_back(make_pair(i, j));
    }
  }
  int max = 0;
  vector<bool> perm;
  for (int i = 0; i < blanks.size() - 3; i++) perm.push_back(false);
  for (int i = 0; i < 3; i++) perm.push_back(true);
  do {
    for (int i = 0; i < perm.size(); i++) {
      if (!perm[i]) continue;
      pii pos = blanks[i];
      tile[pos.first][pos.second] = 1;
    }
    int cand = safearea();
    for (int i = 0; i < perm.size(); i++) {
      if (!perm[i]) continue;
      pii pos = blanks[i];
      tile[pos.first][pos.second] = 0;
    }
    if (cand > max) max = cand;
  } while (next_permutation(perm.begin(), perm.end()));
  printf("%d", max);
}