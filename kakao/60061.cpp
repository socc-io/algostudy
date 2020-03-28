#include <string>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vvpii Tile;

bool check_pillar_install(const Tile &tile, int x, int y) {
  int n = tile.size() - 1;
  if (y == n) return false;
  if (y == 0 || tile[x][y].second || tile[x][y-1].first) return true;
  if (x > 0 && tile[x-1][y].second) return true;
  return false;
}

bool check_board_install(const Tile &tile, int x, int y) {
  int n = tile.size() - 1;
  if (x == n || y == 0) return false;
  if (y > 0) {
    if (tile[x][y-1].first) return true;
    if (x < n && tile[x+1][y-1].first) return true;
  }
  if (x > 0 && x < n && tile[x-1][y].second && tile[x+1][y].second) return true;
  return false;
}

bool check_pillar_uninstall(const Tile& tile, int x, int y) {
  int n = tile.size() - 1;
  if (y < n) {
    if (tile[x][y+1].second && !check_board_install(tile, x, y+1)) return false;
    if (tile[x][y+1].first && !check_pillar_install(tile, x, y+1)) return false;
    if (x > 0 && tile[x-1][y+1].second && !check_board_install(tile, x-1, y+1)) return false;
  }
  return true;
}

void uninstall_pillar(Tile &tile, int x, int y) {
  if (tile[x][y].first == 0) return;
  tile[x][y].first = 0;
  if (!check_pillar_uninstall(tile, x, y)) tile[x][y].first = 1;
}

bool check_board_uninstall(const Tile& tile, int x, int y) {
  int n = tile.size() - 1;
  if (tile[x][y].first && !check_pillar_install(tile, x, y)) return false;
  if (x > 0 && tile[x-1][y].second && !check_board_install(tile, x-1, y)) return false;
  if (x < n) {
    if (tile[x+1][y].second && !check_board_install(tile, x+1, y)) return false;
    if (tile[x+1][y].first && !check_pillar_install(tile, x+1, y)) return false;
  }
  return true;
}

void uninstall_board(Tile &tile, int x, int y) {
  if (tile[x][y].second == 0) return;
  tile[x][y].second = 0;
  if (!check_board_uninstall(tile, x, y)) tile[x][y].second = 1;
}

vvi solution(int n, vvi build_frame) {
  vvi ans;
  Tile tile(n+1, vpii(n+1, {0, 0}));
  for (auto frame: build_frame) {
    int x = frame[0], y = frame[1], a = frame[2], b = frame[3];
    if (b) { // install
      if (a) { // board
        if (check_board_install(tile, x, y))
          tile[x][y].second = 1;
      } else { // pillar
        if (check_pillar_install(tile, x, y))
          tile[x][y].first = 1;
      }
    } else { // uninstall
      if (a) { // board
        uninstall_board(tile, x, y);
      } else { // pillar
        uninstall_pillar(tile, x, y);
      }
    }
  }
  for (int x = 0; x <= n; x++) {
    for (int y = 0; y <= n; y++) {
      if (tile[x][y].first)  ans.push_back({x, y, 0});
      if (tile[x][y].second) ans.push_back({x, y, 1});
    }
  }
  return ans;
}

int main(void)
{
  return 0;
}
