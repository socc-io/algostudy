#include <cstdio>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef int pstate[][50];

const int dd[4][2] = {
  {1,0},{-1,0},{0,1},{0,-1}
};
const int win_dir[2][4][2] = {
  {{-1,0},{0,1},{1,0},{0,-1}},
  {{1,0},{0,1},{-1,0},{0,-1}},
};

int r, c, t;
int states[2][50][50];

pii puri[2];

bool outbound(pii pos) {
  if (pos.first < 0 || pos.first >= r) return true;
  if (pos.second < 0 || pos.second >= c) return true;
  return false;
}

void clear(int buf[][50]) {
  for (int i = 0; i < 50; i++) for (int j = 0; j < 50; j++) {
    buf[i][j] = 0;
  }
  for (int i = 0; i < 2; i++) {
    buf[puri[i].first][puri[i].second] = -1;
  }
}

void diffuse(pstate from, pstate to) {
  clear(to);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int amount = from[i][j];
      if (amount == -1) continue;
      int away = amount / 5;
      for (int di = 0; di < 4; di++) {
        int nx = i + dd[di][0];
        int ny = j + dd[di][1];
        if (outbound(make_pair(nx, ny))) continue;
        if (from[nx][ny] == -1) continue;
        to[nx][ny] += away;
        amount -= away;
      }
      to[i][j] += amount;
    }
  }
}

void blow(pstate from) {
  for (int i = 0; i < 2; i++) {
    pii cur = puri[i];
    cur.first += win_dir[i][0][0];
    cur.second += win_dir[i][0][1];
    int dir_index = 0;
    while (1) {
      int nx = cur.first + win_dir[i][dir_index][0];
      int ny = cur.second + win_dir[i][dir_index][1];
      if (puri[i].first == nx && puri[i].second == ny) break;
      if (outbound(make_pair(nx, ny)) || (dir_index == 2 && cur.first == puri[i].first)) {
        ++dir_index;
        continue;
      }
      from[cur.first][cur.second] = from[nx][ny];
      cur.first = nx;
      cur.second = ny;
    }
    from[puri[i].first][puri[i].second+1]=0;
  }
}

void print(pstate from) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      printf("%2d ", from[i][j]);
    }
    puts("");
  }
}

int main(void)
{
  puri[0].first = -1;
  scanf("%d%d%d", &r, &c, &t);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      int tmp; scanf("%d", &tmp);
      states[0][i][j] = tmp;
      if (tmp == -1) {
        if (puri[0].first == -1) {
          puri[0].first = i;
          puri[0].second = j;
        } else {
          puri[1].first = i;
          puri[1].second = j;
        }
      }
    }
  }
  auto a = states[0];
  auto b = states[1];
  // print(a);
  while(t--) {
    diffuse(a, b);
    // puts("");
    // print(b);
    blow(b);
    // puts("");
    // print(b);
    swap(a, b);
  };

  int sum = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (a[i][j] == -1) continue;
      sum += a[i][j];
    }
  }
  printf("%d", sum);
}
