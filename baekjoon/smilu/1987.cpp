/*

# 문제

세로 R칸, 가로 C칸으로 된 표 모양의 보드가 있다. 보드의 각 칸에는 대문자 알파벳이 하나씩 적혀 있고, 좌측 상단 칸 (1행 1열) 에는 말이 놓여 있다.
말은 상하좌우로 인접한 네 칸 중의 한 칸으로 이동할 수 있는데, 새로 이동한 칸에 적혀 있는 알파벳은 지금까지 지나온 모든 칸에 적혀 있는 알파벳과는 달라야 한다.
즉, 같은 알파벳이 적힌 칸을 두 번 지날 수 없다.
좌측 상단에서 시작해서, 말이 최대한 몇 칸을 지날 수 있는지를 구하는 프로그램을 작성하시오. 말이 지나는 칸은 좌측 상단의 칸도 포함된다.

# 입력

첫째 줄에 R과 C가 빈칸을 사이에 두고 주어진다. (1<=R,C<=20) 둘째 줄부터 R개의 줄에 걸쳐서 보드에 적혀 있는 C개의 대문자 알파벳들이 빈칸 없이 주어진다.

# 출력

첫째 줄에 말이 지날 수 있는 최대의 칸 수를 출력한다.

# 예제 입력

2 4
CAAB
ADCB

# 예제 출력

3

*/

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <cstdint>
using namespace std;

const int dd[4][2] = {
  {-1,0},{0,1},{1,0},{0,-1},
};

int r, c;
char tile[20][20];

struct state {
  uint32_t alphabets;
  uint8_t x;
  uint8_t y;
  uint16_t d;
};

int eat_alphabet(int prev, int alphabet) {
  return prev | (1 << alphabet);
}
bool ate_alphabet(int alphabets, int alphabet) {
  return (alphabets & (1 << alphabet)) > 0;
}

state init_state() {
  state s;
  s.alphabets = eat_alphabet(0, tile[0][0]);
  s.x = 0;
  s.y = 0;
  s.d = 1;
  return s;
}

bool outbound(int x, int y) {
  return x < 0 || x >= r || y < 0 || y >= c;
}

int bfs() {
  queue<state> q;
  // set<state> visit;
  q.push(init_state());
  int max_d = 1;
  while (!q.empty()) {
    state u = q.front();
    // printf("%d, %d, %d, %d\n", u.alphabets, u.x, u.y, u.d);
    q.pop();
    for (int di = 0; di < 4; di++) {
      int nx = u.x + dd[di][0];
      int ny = u.y + dd[di][1];
      if (outbound(nx, ny) || ate_alphabet(u.alphabets, tile[nx][ny])) continue;
      state next;
      next.alphabets = eat_alphabet(u.alphabets, tile[nx][ny]);
      next.x = nx;
      next.y = ny;
      next.d = u.d + 1;
      if (next.d > max_d) max_d = next.d;
      // if (visit.find(next) != visit.end()) continue;
      q.push(next);
    }
  }
  return max_d;
}

int main(void)
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> r >> c;
  for (int i = 0; i < r; i++) {
    string tmp; cin >> tmp;
    for (int j = 0; j < c; j++) {
      tile[i][j] = tmp[j] - 'A';
    }
  }
  int ans = bfs();
  cout << ans << '\n';
}