#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

const int dd[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

int h, w;
bool visit[102][102];
char tile[102][102];
char line_buf[102];

bool is_door(char c) {
  return 'A' <= c && c <= 'Z';
}
bool is_key(char c) {
  return 'a' <= c && c <= 'z';
}
bool outbound(int x, int y) {
  return x < 0 || x >= h || y < 0 || y >= w;
}
void remove_char(char d) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (tile[i][j] == d) tile[i][j] = '.';
    }
  }
}
void clear_visit() {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      visit[i][j] = false;
    }
  }
}

void solve()
{
  scanf("%d%d", &h, &w);
  for (int i = 0; i < h; i++) {
    scanf("%s", &tile[i+1][1]);
    tile[i+1][0] = 0;
    tile[i+1][w+1] = 0;
  }
  h += 2; w += 2;
  for (int i = 0; i < w; i++) {
    tile[0][i] = 0;
    tile[h-1][i] = 0;
  }

  scanf("%s", line_buf);
  vector<bool> removed_key(26, false);
  for (char *ch = line_buf; *ch != 0 && *ch != '0'; ch++) {
    remove_char(*ch - 32);
    removed_key[*ch - 97] = true;
  }
  
  int ans = 0;
  queue<pii> q;
  q.push(make_pair(0, 0));
  clear_visit();
  while (!q.empty()) {
    pii u = q.front(); q.pop();
    int x = u.first, y = u.second;

    if (outbound(x, y)) continue;
    char t = tile[x][y];
    if (visit[x][y] || t == '*' || is_door(t)) continue;
    // printf("%d, %d\n", x, y);
    visit[x][y] = true;
    if (t == '$') {
      // printf("Eat (%d, %d)\n", x, y);
      tile[x][y] = '.';
      ++ans;
    } else if (is_key(t)) {
      tile[x][y] = '.';
      if (removed_key[t - 97] == false) {
        removed_key[t - 97] = true;
        remove_char(t - 32);
        clear_visit();
        while (!q.empty()) q.pop();
        q.push(make_pair(x, y));
        continue;
      }
    }
    for (int di = 0; di < 4; di++) {
      q.push(make_pair(x + dd[di][0], y + dd[di][1]));
    }
  }
  printf("%d\n", ans);
}

int main(void)
{
  int t; scanf("%d", &t);
  while(t--) solve();
}
