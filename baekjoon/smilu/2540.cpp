#include <bits/stdc++.h>
using namespace std;

int __counting_sort_cnt[3001];
void counting_sort(
  vector<int>::iterator begin,
  vector<int>::iterator end
) {
  auto & cnt = __counting_sort_cnt;
  memset(cnt, 0x00, sizeof(int) * 3001);
  for (auto it = begin; it != end; it++) {
    cnt[*it]++;
  }
  int pnt = 0;
  for (auto it = begin; it != end; it++) {
    while (cnt[pnt] == 0) ++pnt;
    *it = pnt;
    cnt[pnt]--;
  }
}

inline void print_vi(const vector<int> &vs) {
  for (int v: vs) cout << v << ' '; cout << '\n';
}

inline bool is_odd(int v) { return (bool)(v & 1); }

struct State {
  int n, sum;
  vector<int> es;
  State() {
    while (1) {
      int e; cin >> e;
      es.push_back(e);
      if (cin.eof()) break;
    }
    n = (int)es.size();
    sum = accumulate(es.begin(), es.end(), 0);
    counting_sort(es.begin(), es.end());
  }
  void print() { print_vi(es); }
  int last() { return es[n-1]; }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int k; cin >> k;
  State s;

  // print initialized state
  s.print();

  if (is_odd(s.sum - s.last())) {
    
  }
}
