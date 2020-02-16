/*
 * Solving https://www.acmicpc.net/problem/15652
 */

#include <cstdio>
#include <vector>
using namespace std;

class Solver {
  int N;
  int M;
  vector<int> arr = vector<int>(10);
  void input() {
    scanf("%d %d", &N, &M);
  }
  void select(int num, int level) {
    arr[level] = num;
  }
  void print_arr() {
    for (int i = 0; i < M; i++) {
      printf("%d ", arr[i]);
    }
    puts("");
  }
  int get_begin(int level = 0) {
    if (level == 0) return 1;
    return arr[level - 1];
  }
  void select_and_next(int level = 0) {
    for (int i = get_begin(level); i <= N; i++) {
      select(i, level);
      if (level + 1 == M) {
        print_arr();
      } else {
        select_and_next(level + 1);
      }
    }
  }
public:
  void solve() {
    input();
    select_and_next();
  }
};

int main(void)
{
  Solver solver = Solver();
  solver.solve();
}
