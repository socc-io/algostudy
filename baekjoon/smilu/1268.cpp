#include <bits/stdc++.h>
using namespace std;

int n;
bool adj[1000][1000];
int adj_cnt[1000];

int tile[1000][5];

vector<int> students(int lev, int cls) {
  vector<int> ret;
  for (int i = 0; i < n; i++) {
    if (tile[i][lev] == cls) ret.push_back(i);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> tile[i][j];
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 1; j < 10; j++) {
      auto s = students(i, j);
      for (int k = 0; k < s.size(); k++) {
        for (int l = k+1; l < s.size(); l++) {
          const int p = s[k], q = s[l];
          adj[p][q] = true;
          adj[q][p] = true;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    adj_cnt[i] = count(adj[i], adj[i] + n, true);
  }
  const int mc = *max_element(adj_cnt, adj_cnt + n);
  for (int i = 0; i < n; i++) {
    if (adj_cnt[i] == mc) {
      cout << i+1;
      return 0;
    }
  }
}
