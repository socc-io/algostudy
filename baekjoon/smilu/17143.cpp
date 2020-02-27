/*
https://www.acmicpc.net/problem/17143
*/

#include <iostream>
using namespace std;

#define INF 0x7FFFFFF0

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

struct shark {
  int x;
  int y;
  int vx;
  int vy;
  int size;
  bool dead;
};

void input_shark(shark& s) {
  int speed, direction;
  cin >> s.x >> s.y >> speed >> direction >> s.size;
  s.vx = dd[direction-1][0] * speed;
  s.vy = dd[direction-1][1] * speed;
  s.x -= 1;
  s.y -= 1;
}

int r, c, m;
shark* tile[2][100][100];
shark sharks[10000];

void clear_tile(int ti) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      tile[ti][i][j] = NULL;
    }
  }
}

void move_shark(int ti, shark& s) {
  s.x += s.vx;
  s.y += s.vy;

  while(1) {
    if (s.x < 0) {
      s.x *= -1;
      s.vx *= -1;
    } else if (s.x >= r) {
      s.x = 2 * (r-1) - s.x;
      s.vx *= -1;
    } else break;
  }

  while(1) {
    if (s.y < 0) {
      s.y *= -1;
      s.vy *= -1;
    } else if (s.y >= c) {
      s.y = 2 * (c-1) - s.y;
      s.vy *= -1;
    } else break;
  }

  if (tile[ti][s.x][s.y] != NULL) {
    shark *enemy = tile[ti][s.x][s.y];
    if (s.size > enemy->size) {
      enemy->dead = true;
    } else {
      s.dead = true;
      return;
    }
  }

  tile[ti][s.x][s.y] = &s;
}

int find_shark(int col) {
  int min_xi = -1;
  int min_x = INF;
  for (int i = 0; i < m; i++) {
    if (sharks[i].dead) continue;
    if (sharks[i].y != col) continue;
    if (sharks[i].x < min_x) {
      min_x = sharks[i].x;
      min_xi = i;
    }
  }
  return min_xi;
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> r >> c >> m;
  for (int i = 0; i < m; ++i) {
    input_shark(sharks[i]);
    tile[0][sharks[i].x][sharks[i].y] = &sharks[i];
  }

  int ans = 0;
  for (int i = 0; i < c; i++) {
    int shark_idx = find_shark(i);
    if (shark_idx != -1) {
      sharks[shark_idx].dead = true;
      // printf("t: %d, ate: %d, size: %d\n", i, shark_idx, sharks[shark_idx].size);
      ans += sharks[shark_idx].size;
    } else {
      // puts("nothing");
    }
    clear_tile((i+1)%2);
    for (int j = 0; j < m; j++) {
      if (sharks[j].dead) continue;
      move_shark((i+1) % 2, sharks[j]);
    }
    for (int j = 0; j < m; j++) {
      shark &s = sharks[j];
      if (s.dead) continue;
      // printf("  shark (%d, %d, %d, %d, %d)\n", s.x,s.y,s.vx,s.vy,s.size);
    }
  }

  cout << ans << '\n';
}
