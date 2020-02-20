
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFF0

typedef pair<int, int> pii;

const int dd[4][2] = {
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1},
};

int n;
char tile[20][20];
int dist[20][20];

pii sp;
int shark_size = 2;
int eat_count = 0;

void clear_dist() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    dist[i][j] = INF;
  }
}
pii find_food() {
  queue<pii> q;
  vector<pii> fps;
  clear_dist();
  dist[sp.first][sp.second] = 0;
  q.push(sp);
  while(!q.empty()) {
    pii u = q.front();
    q.pop();
    int d = dist[u.first][u.second];
    for (int i = 0; i < 4; i++) {
      int nx = u.first + dd[i][0];
      int ny = u.second + dd[i][1];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      if (tile[nx][ny] > shark_size) continue;
      if (dist[nx][ny] <= d + 1) continue;
      dist[nx][ny] = d + 1;
      if (tile[nx][ny] != 0 && tile[nx][ny] < shark_size) {
        if (fps.size() == 0) fps.push_back(make_pair(nx, ny));
        else {
          int th = dist[fps[0].first][fps[0].second];
          if (d + 1 < th) {
            fps.clear();
            fps.push_back(make_pair(nx, ny));
          } else if (d + 1 == th) {
            fps.push_back(make_pair(nx, ny));
          }
        }
      }
      q.push(make_pair(nx, ny));
    }
  }
  if (fps.empty()) return make_pair(-1, -1);
  sort(fps.begin(), fps.end());
  return fps[0];
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
     for (int j = 0; j < n; j++) {
       int tmp; scanf("%d", &tmp);
       if (tmp == 9) {
         sp = make_pair(i, j);
         continue;
       }
       tile[i][j] = (char)tmp;
     }
  }

  int time = 0;
  while(1) {
    pii fp = find_food();
    if (fp.first == -1) break;

    int fd = dist[fp.first][fp.second];
    tile[fp.first][fp.second] = 0;
    sp = fp;
    ++eat_count;
    if (eat_count >= shark_size) {
      eat_count = 0;
      shark_size++;
    }
    time += fd;
  }

  printf("%d", time);
}