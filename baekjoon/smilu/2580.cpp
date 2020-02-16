/*
 * Solving https://www.acmicpc.net/problem/2580
 * Sudoku
 */

#include <cstdio>
#include <vector>
using namespace std;

#define TILE_UNDEFINED 0

class Tile {
  int value;
  bool candidates[10];
public:
  Tile() {
    value = 0;
    for (int i = 0; i < 10; i++) {
      candidates[i] = false;
    }
  }
  void set_value(int value) {
    this->value = value;
  }
  int get_value() {
    return value;
  }
  void candidate_all() {
    for (int i = 1; i <= 9; i++) {
      candidates[i] = true;
    }
  }
  void candidate(int value) {
    if (value >= 1 && value <= 9) {
      candidates[value] = true;
    }
  }
  void decandidate(int value) {
    if (value >= 1 && value <= 9) {
      candidates[value] = false;
    }
  }
  bool is_candidate(int value) {
    return candidates[value];
  }
  void undefine() {
    this->value = TILE_UNDEFINED;
  }
  bool is_undefined() {
    return value == TILE_UNDEFINED;
  }
};

class Sudoku {
  Tile tiles[9][9];
public:
  void input() {
    for (int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
        int val;
        scanf("%d", &val);
        if (val == 0) {
          tiles[i][j].undefine();
        } else {
          tiles[i][j].set_value(val);
        }
      }
    }
  }
  void decandidate_block(int x, int y) {
    int sx = (x / 3) * 3;
    int sy = (y / 3) * 3;
    for (int ix = sx; ix < sx + 3; ++ix) {
      for (int iy = sy; iy < sy + 3; ++iy) {
        if(ix == x && iy == y) continue;
        int ivalue = tiles[ix][iy].get_value();
        tiles[x][y].decandidate(ivalue);
      }
    }
  }
  void decandidate_cross(int x, int y) {
    for (int i = 0; i < 9; i++) {
      if (i == y) continue;
      tiles[x][y].decandidate(
        tiles[x][i].get_value()
      );
    }
    for (int i = 0; i < 9; i++) {
      if (i == x) continue;
      tiles[x][y].decandidate(
        tiles[i][y].get_value()
      );
    }
  }
  void update_candidates(int x, int y) {
    tiles[x][y].candidate_all();
    decandidate_block(x, y);
    decandidate_cross(x, y);
  }
  pair<int, int> find_next_undefined(int x, int y) {
    while (x != 9) {
      if (tiles[x][y].is_undefined()) return make_pair(x, y);
      // next iterate
      ++y;
      if (y >= 9) {
        ++x;
        y = 0;
      }
    }
    return make_pair(9, 0);
  }
  bool select(int x, int y) {
    update_candidates(x, y);
    for (int i = 1; i <= 9; i++) {
      if (!tiles[x][y].is_candidate(i)) continue;
      tiles[x][y].set_value(i);
      pair<int, int> next = find_next_undefined(x, y);
      if (next.first == 9) return true;
      else {
        if (select(next.first, next.second)) return true;
      }
    }
    return false;
  }
  bool autofill() {
    pair<int ,int> first = find_next_undefined(0, 0);
    return select(first.first, first.second);
  }
  void print_tile() {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        printf("%d ", tiles[i][j].get_value());
      } puts("");
    }
  }
  bool test() {
    bool pin[10];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 10; k++) pin[k] = false;
        for (int k = 0; k < 3; k++) {
          for(int m = 0; m < 3; m++) {
            int x = i * 3 + k;
            int y = j * 3 + m;
            int v = tiles[x][y].get_value();
            if (pin[v]) return false;
            pin[v] = true;
          }
        }
        for (int k = 1; k <= 9; k++) {
          if (!pin[k]) return false;
        }
      }
    }
    for (int i = 0; i < 9; i++) {
      for (int j = 1; j <= 9; j++) {
        pin[j] = false;
      }
      for (int j = 0; j < 9; j++) {
        int v = tiles[i][j].get_value();
        if (pin[v]) return false;
        pin[v] = true;
      }
      for (int j = 1; j <= 9; j++) {
        if (!pin[j]) return false;
      }
    }
    for (int i = 0; i < 9; i++) {
      for (int j = 1; j <= 9; j++) {
        pin[j] = false;
      }
      for (int j = 0; j < 9; j++) {
        int v = tiles[j][i].get_value();
        if (pin[v]) return false;
        pin[v] = true;
      }
      for (int j = 1; j <= 9; j++) {
        if (!pin[j]) return false;
      }
    }
    return true;
  }
};

int main(void)
{
  Sudoku game = Sudoku();
  game.input();
  game.autofill();
  game.print_tile();
  puts(game.test() ? "SUCCESS" : "FAIL");
}
