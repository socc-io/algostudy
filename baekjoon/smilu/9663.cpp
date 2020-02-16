#include <cstdio>
#include <vector>
using namespace std;

class NQueen {
  int N;
  int count;
  int queens[15];
  bool banned[15][15];
  void clean_banned_row(int row) {
    for (int i = 0; i < 15; i++) {
      banned[row][i] = false;
    }
  }
  void ban(int row, int col) {
    if (col >= 0 && col < N) {
      banned[row][col] = true;
    }
  }
  void select_on_row(int row) {
    clean_banned_row(row);
    for (int prev_row = 0; prev_row < row; ++prev_row) {
      int diff_row = row - prev_row;
      ban(row, queens[prev_row] + diff_row);
      ban(row, queens[prev_row] - diff_row);
      ban(row, queens[prev_row]);
    }
    for (int col = 0; col < N; ++col) {
      if (banned[row][col]) continue;
      queens[row] = col;
      int next_row = row + 1;
      if (next_row == N) {
        count++;
      } else {
        select_on_row(next_row);
      }
    }
  }
public:
  NQueen(int N) {
    this->N = N;
  }
  int solve() {
    count = 0;
    select_on_row(0);
    return count;
  }
};

int main(void)
{
  int N;
  scanf("%d", &N);
  NQueen nq = NQueen(N);
  printf("%d", nq.solve());
}
