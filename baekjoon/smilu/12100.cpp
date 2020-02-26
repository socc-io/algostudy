#include <vector>
#include <cstdio>
using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<bool>> vvb;

const int scan_dir[4][6] = {
  {0, 1, 0, 1, 0, 0},
  {1, 0, 0, 0, -1, 1},
  {0, -1, 1, 1, 0, 0},
  {1, 0, 0, 0, 1, 0},
};
const int next_dir[4][2] = {
  {-1, 0}, {0, 1}, {1, 0}, {0, -1},
};

inline bool inbound(int x, int y, int n) {
  return x >= 0 && x < n && y >= 0 && y < n;
}

void move_board(vvi &board, int dir) {
  int n = board.size();
  int* scan = (int*)scan_dir[dir];
  int* next = (int*)next_dir[dir];
  vvb lock(n, vector<bool>(n, false));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x = i * scan[0] + j * scan[1] + (n - 1) * scan[2];
      int y = i * scan[3] + j * scan[4] + (n - 1) * scan[5];
      if (board[x][y] == 0) continue;
      int nx, ny;
      while(1) {
        nx = x + next[0];
        ny = y + next[1];
        if (inbound(nx, ny, n) && board[nx][ny] == 0) {
          board[nx][ny] = board[x][y];
          board[x][y] = 0;
        } else break;
        x = nx;
        y = ny;
      }
      if (inbound(nx, ny, n) && board[nx][ny] == board[x][y] && !lock[nx][ny]) {
        lock[nx][ny] = true;
        board[nx][ny] <<= 1;
        board[x][y] = 0;
      }
    }
  }
}

void print_board(vvi & board) {
  int n = board.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%2d ", board[i][j]);
    } puts("");
  }
}

void copy_board(vvi &dest, vvi &src) {
  int n = dest.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

int get_max(vvi &board) {
  int n = board.size();
  int max = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] > max) max = board[i][j];
    }
  }
  return max;
}

int find2048(vvi &board, int left) {
  if (left == 0) return get_max(board);
  int n = board.size();
  int max = 0;
  vvi copy(n, vi(n));
  for (int i = 0; i < 4; i++) {
    copy_board(copy, board);
    move_board(copy, i);
    int res = find2048(copy, left - 1);
    if (res > max) max = res;
  }
  return max;
}

int main(void)
{
  int n;
  scanf("%d", &n);
  vvi board(n, vi(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp; scanf("%d", &tmp);
      board[i][j] = tmp;
    }
  }
  // move_board(board, 0);
  // print_board(board);

  printf("%d", find2048(board, 5));
}
