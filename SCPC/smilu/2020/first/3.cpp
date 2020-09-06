#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int inf = 0x3f3f3f3f;

struct Point {
  int neigh;
  int down;
  int line;
} points[5555];
int piv_points;

int dp[5555][1515];

vector<int> line[1515];

int n, k, m;

int get_dp(int i_point, int t_line) {
  int &res = dp[i_point][t_line];
  if (res != -1) return res;
  const int nei_point = points[i_point].neigh;
  const int down_point = points[i_point].down;
  const int nei_down_point = points[nei_point].down;
  res = min(inf, min(get_dp(nei_down_point, t_line), get_dp(down_point, t_line) + 1));
  return res;
}

int solve() {df
  cin >> n >> k >> m;
  
  for (int i = 0; i < n; i++) line[i].clear();
  memset(dp, 0xFF, sizeof(dp));
  piv_points = 0;

  for (int i = 0; i < k; i++) {
    int l1, l2; cin >> l1 >> l2; --l1; --l2;
    int p1 = piv_points++;
    int p2 = piv_points++;
    line[l1].push_back(p1);
    line[l2].push_back(p2);
    points[p1].neigh = p2;
    points[p2].neigh = p1;
    points[p1].line = l1;
    points[p2].line = l2;
  }
  for (int i = 0; i < n; i++) {
    int p = piv_points++;
    line[i].push_back(p);
    points[p].down = -1;
    points[p].neigh = p;
    points[p].line = i;
    for (int j = 0; j < n; j++) {
      dp[p][j] = (i == j ? 0 : inf);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < line[i].size() - 1; j++) {
      points[line[i][j]].down = line[i][j+1];
    }
  }

  int ans = 0;
  for (int i = 0; i < m; i++) {
    int l1, l2; cin >> l1 >> l2; --l1; --l2;
    int ip = line[l1][0];
    int res = get_dp(ip, l2);
    if (res == inf) res = -1;
    ans += res;
  }

  return ans;
}

int main(int argc, char** argv)
{
	int T, test_case;
  setbuf(stdout, NULL);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		cout << "Case #" << test_case+1 << endl;
		cout << solve() << endl;
	}

	return 0;
}