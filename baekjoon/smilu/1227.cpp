#include <cstdio>
#include <queue>
using namespace std;

typedef pair<int,int> pii;
typedef long long lld;

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int b, s;
bool obs[2001][2001];
char pr[2001][2001];
int h[2001][2001];
lld ans[2];

void linear(int h, int s) {
  int d = h >> 1;
  ans[s-1] += d;
  ans[2-s] += d + (h & 1);
}

void q_square(int h, int s) {
  int a = h + 1;
  if (a <= 0) return;
  lld b = a >> 1;
  if (a & 1) {
    ans[s-1] += (b+1)*(b+1);
    ans[2-s] += b*(b+1);
  } else {
    ans[s-1] += b*b;
    ans[2-s] += b*(b+1);
  }
}

int main(void)
{
  scanf("%d%d", &b, &s);
  for (int i = 0; i < b; i++) {
    int x, y; scanf("%d%d", &x, &y);
    obs[x+1000][y+1000] = true;
  }

  pr[1000][1000] = 1;
  h[1000][1000] = s;
  ans[0]++;
  queue<pii> q;
  q.push({1000, 1000});
  while (!q.empty()) {
    pii u = q.front();
    q.pop();
    char next_pr = 3 - pr[u.first][u.second];
    int next_h = h[u.first][u.second] - 1;
    for (int di = 0; di < 4; di++) {
      int nx = u.first + dd[di][0];
      if (nx < 0 || nx > 2000) continue;
      int ny = u.second + dd[di][1];
      if (ny < 0 || ny > 2000) continue;
      if (obs[nx][ny] || pr[nx][ny]) continue;
      pr[nx][ny] = next_pr;
      h[nx][ny] = next_h;
      ans[next_pr-1]++;
      if (next_h) {
        q.push({nx, ny});
      }
    }
  }

  for (int i = 0; i < 2001; i++) {
    linear(h[0][i], pr[0][i]); // top
    linear(h[i][0], pr[i][0]); // left
    linear(h[i][2000], pr[i][2000]); // right
    linear(h[2000][i], pr[2000][i]); // bottom
  }
  q_square(h[0][0] - 2, pr[0][0]);
  q_square(h[2000][0] - 2, pr[2000][0]);
  q_square(h[0][2000] - 2, pr[0][2000]);
  q_square(h[2000][2000] - 2, pr[2000][2000]);

  printf("%lld %lld\n", ans[0], ans[1]);
}
