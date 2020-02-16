#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
  cin.tie(NULL);
  ios::sync_with_stdio(false);

  int N, M;
  set<string> st;
  vector<string> rs;

  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    st.insert(s);
  }
  for (int i = 0; i < M; i++) {
    string s; cin >> s;
    if (st.find(s) != st.end()) {
      rs.push_back(s);
    }
  }

  sort(rs.begin(), rs.end());

  cout << rs.size() << '\n';
  for (auto it = rs.begin(); it != rs.end(); ++it) {
    cout << *it << '\n';
  }
}