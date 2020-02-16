/*
 * Solving https://www.acmicpc.net/problem/15651
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
  void select_and_next(int level = 0) {
    for (int i = 1; i <= N; i++) {
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
