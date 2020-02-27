/*
http://noj.am/17404

## 문제

RGB거리에 사는 사람들은 집을 빨강, 초록, 파랑중에 하나로 칠하려고 한다.
또한, 그들은 모든 이웃은 같은 색으로 칠할 수 없다는 규칙도 정했다.
집 i의 이웃은 집 i-1과 집 i+1이고, 첫 집과 마지막 집도 이웃이다.

각 집을 빨강으로 칠할 때 드는 비용, 초록으로 칠할 때 드는 비용, 파랑으로 드는 비용이 주어질 때,
모든 집을 칠하는 비용의 최솟값을 구하는 프로그램을 작성하시오.

## 입력

첫째 줄에 집의 수 N이 주어진다.
N은 1,000보다 작거나 같다.
둘째 줄부터 N개의 줄에 각 집을 빨강으로, 초록으로, 파랑으로 칠하는 비용이 주어진다.
비용은 1,000보다 작거나 같은 자연수이다.

## 출력

첫째 줄에 모든 집을 칠하는 비용의 최솟값을 출력한다.

## 예제 입력

3
26 40 83
49 60 57
13 89 99

## 예제 출력

110

*/

int n;
int costs[1000][3];

int dp[3][1000][3];

#include <iostream>
using namespace std;

#define INF 0x7FFFF000

int min(int a, int b) { return a < b ? a : b; }
void inspect(int fc, int i) {
  dp[fc][i][0] = min(dp[fc][i-1][1], dp[fc][i-1][2]) + costs[i][0];
  dp[fc][i][1] = min(dp[fc][i-1][0], dp[fc][i-1][2]) + costs[i][1];
  dp[fc][i][2] = min(dp[fc][i-1][0], dp[fc][i-1][1]) + costs[i][2];
}

int main(void)
{
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> costs[i][0] >> costs[i][1] >> costs[i][2];
  }

  dp[0][0][0] = costs[0][0];
  dp[0][0][1] = INF;
  dp[0][0][2] = INF;

  dp[1][0][0] = INF;
  dp[1][0][1] = costs[0][1];
  dp[1][0][2] = INF;

  dp[2][0][0] = INF;
  dp[2][0][1] = INF;
  dp[2][0][2] = costs[0][2];

  for (int i = 1; i < n - 1; i++) {
    inspect(0, i);
    inspect(1, i);
    inspect(2, i);
  }

  int ans = INF;
  for (int i = 0; i < 3; i++) {  // first home color index
    for (int j = 0; j < 3; j++) {  // last-1 home color index
      for (int k = 0; k < 3; k++) {  // last home color index
        if (k == i || k == j) continue;
        int candidate = dp[i][n-2][j] + costs[n-1][k];
        if (candidate < ans) ans = candidate;
      }
    }
  }
  cout << ans << '\n';
}
