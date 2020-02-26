#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> pii;
#define INF 0x7FFFFFF0

const int dd[4][2] = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1},
};

int n, m;
char tile[10][10];
char buf[11];
pii red_pos, blue_pos, hole_pos;
int i_state;

int pack(pii rp, pii bp) {
  int rx = rp.first  << 12;
  int ry = rp.second << 8;
  int bx = bp.first  << 4;
  int by = bp.second;
  return rx | ry | bx | by;
}
int get_index(int packed) {
  int rx = (packed & 0xF000) >> 12;
  int ry = (packed & 0x0F00) >> 8;
  int bx = (packed & 0x00F0) >> 4;
  int by = (packed & 0x000F);
  return rx * 1000 + ry * 100 + bx * 10 + by;
}
pair<pii,pii> unpack(int packed) {
  int rx = (packed & 0xF000) >> 12;
  int ry = (packed & 0x0F00) >> 8;
  int bx = (packed & 0x00F0) >> 4;
  int by = (packed & 0x000F);
  return make_pair(make_pair(rx, ry), make_pair(bx, by));
}

pii move_ball(int dir, pii c_ball, pii o_ball) {
  pii c_pos = c_ball;
  while(1) {
    c_pos.first += dd[dir][0];
    c_pos.second += dd[dir][1];
    if (c_pos.first < 0 || c_pos.first >= n) break;
    if (c_pos.second < 0 || c_pos.second >= m) break;
    if (c_pos == hole_pos) return make_pair(15, 15);
    if (tile[c_pos.first][c_pos.second]) break;
    if (c_pos.first == o_ball.first && c_pos.second == o_ball.second) break;
  }
  c_pos.first -= dd[dir][0];
  c_pos.second -= dd[dir][1];
  return c_pos;
}

int move_balls(int prev, int dir) {
  auto unpacked = unpack(prev);
  auto rp = unpacked.first;
  auto bp = unpacked.second;

  bool red_first = true;
       if (dir == 0 && rp.first  > bp.first ) red_first = false;
  else if (dir == 1 && rp.second < bp.second) red_first = false;
  else if (dir == 2 && rp.first  < bp.first ) red_first = false;
  else if (dir == 3 && rp.second > bp.second) red_first = false;

  pii mrp, mbp;
  if (red_first) {
    mrp = move_ball(dir, rp, bp);
    mbp = move_ball(dir, bp, mrp);
  } else {
    mbp = move_ball(dir, bp, rp);
    mrp = move_ball(dir, rp, mbp);
  }

  return pack(mrp, mbp);
}

void print(int s) {
  auto unpacked = unpack(s);
  auto rp = unpacked.first;
  auto bp = unpacked.second;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (rp.first == i && rp.second == j) printf("R");
      else if (bp.first == i && bp.second == j) printf("B");
      else if (hole_pos.first == i && hole_pos.second == j) printf("O");
      else printf(tile[i][j] ? "#" : ".");
    } puts("");
  } puts("");
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    for (int j = 0; j < m; j++) {
      if (buf[j] == '#') tile[i][j] = 1;
      else if (buf[j] == '.') tile [i][j] = 0;
      else if (buf[j] == 'R') {
        red_pos = make_pair(i, j);
      } else if (buf[j] == 'B') {
        blue_pos = make_pair(i, j);
      } else if (buf[j] == 'O') {
        hole_pos = make_pair(i, j);
      }
    }
  }
  i_state = pack(red_pos, blue_pos);
  vector<int> dist(10000, INF);
  queue<int> q;
  q.push(i_state);
  dist[get_index(i_state)] = 0;
  int ans = -1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    int ui = get_index(u);
    int nd = dist[ui] + 1;
    if (nd > 10) continue;
    for (int i = 0; i < 4; i++) {
      int v = move_balls(u, i);
      auto unv = unpack(v);
      auto rp = unv.first;
      auto bp = unv.second;
      if (rp.first == 15 && bp.first != 15) {
        ans = nd;
        break;
      }
      if (rp.first == 15 || bp.first == 15) continue;
      int vi = get_index(v);
      if (dist[vi] < nd) continue;
      dist[vi] = nd;
      q.push(v);
    }
    if (ans != -1) break;
  }
  printf("%d", ans);
}
