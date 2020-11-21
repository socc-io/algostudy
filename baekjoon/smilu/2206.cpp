#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef priority_queue<pi, vector<pi>, greater<pi>> pq;

const int dd[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
const int inf = 0x3f3f3f3f;
const int state_size = (1 << 21);

int n, m;
char tile[1010][1010];

bool check_range(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m; 
}

struct State {
  int x, y, p;
  State(int x, int y, int p): x(x),y(y),p(p) {}
  State(int id) {
    x = (id >> 11);
    y = (id >> 1) & 0x3ff;
    p = id & 1;
  }
  int id() {
    return (x << 11) | (y << 1) | p;
  }
  vector<State> next() {
    vector<State> res;
    for (int di = 0; di < 4; di++) {
      int nx = x + dd[di][0], ny = y + dd[di][1];
      if (!check_range(nx, ny)) continue;
      if (tile[nx][ny] == '1') {
        if (p > 0) {
          res.push_back(State(nx, ny, 0));
        }
      } else {
        res.push_back(State(nx, ny, p));
      }
    }
    return res;
  }
};

// return minimum distance from (0, 0, 1) to every states
int dijkstra() {
  vector<int> dist(state_size, inf);
  vector<bool> visit(state_size, false);
  pq q;

  State start(0, 0, 1);
  int start_id = start.id();

  dist[start_id] = 0;
  q.push(make_pair(0, start_id));

  while(!q.empty()) {
    int iud = q.top().first + 1;
    int uid = q.top().second; q.pop();
    State u(uid);
    if (visit[uid]) continue;
    visit[uid] = true;
    for (State v: u.next()) {
      int vid = v.id();
      if (visit[vid]) continue;
      if (dist[vid] > iud) {
        dist[vid] = iud;
        q.push(make_pair(iud, vid));
      }
    }
  }

  int ans_1 = dist[State(n-1, m-1, 0).id()];
  int ans_2 = dist[State(n-1, m-1, 1).id()];
  int ans = min(ans_1, ans_2);

  return ans == inf ? -1 : (ans + 1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> tile[i];
  cout << dijkstra() << '\n';
}
