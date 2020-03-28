#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

void print_vvi(const vvi &p) {
  int n = p.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << p[i][j] << ' ';
    } cout << '\n';
  }
}

int sum(const vvi &p) {
  int n = p.size(), res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res += p[i][j];
    }
  }
  return res;
}

vvi rotate(const vvi &p) {
  int n = p.size();
  vvi q(n, vi(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      q[i][j] = p[n-1-j][i];
    }
  }
  return q;
}

bool match(const vvi &key, const vvi &lock, int num_lock, pii offset) {
  int nk = key.size(), nl = lock.size(), unlock = 0;
  int xb = max(offset.first, 0), xe = min(offset.first + nk, nl);
  int yb = max(offset.second, 0), ye = min(offset.second + nk, nl);
  for (int x = xb; x < xe; x++) {
    for (int y = yb; y < ye; y++) {
      int i = x - offset.first, j = y - offset.second;
      if (key[i][j] + lock[x][y] == 1) {
        if (lock[x][y] == 0) ++unlock;
      } else {
        return false;
      }
    }
  }
  return unlock == num_lock;
}

bool solution(vvi key, vvi lock) {
  int nk = key.size(), nl = lock.size();
  vvi keys[4];
  keys[0] = key;
  keys[1] = rotate(keys[0]);
  keys[2] = rotate(keys[1]);
  keys[3] = rotate(keys[2]);
  int num_lock = nl*nl - sum(lock);
  for (int r = 0; r < 4; r++) {
    for (int x = 1-nk; x < nl; x++) {
      for (int y = 1-nk; y < nl; y++) {
        bool match_res = match(keys[r], lock, num_lock, {x, y});
        if (match_res) {
          return true;
        }
      }
    }
  }
  return false;
}

int main(void) {
  vvi key = {{0,0,1},{0,0,0},{0,0,0}};
  vvi lock = {{1,0,0},{1,1,1},{1,1,1}};
  cout << match(key, lock, 2, {-1, -2}) << endl;
}
