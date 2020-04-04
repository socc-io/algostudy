#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
  int skill;
  int algos;
  void get_input() {
    int n;
    scanf("%d%d", &n, &skill);
    algos = 0;
    for (int i = 0; i < n; i++) {
      int t; scanf("%d", &t); --t;
      algos |= (1 << t);
    }
  }
  bool operator<(const Person &p) const {
    return skill < p.skill;
  }
};

bool operator<(const int a, const Person &b) {
  return a < b.skill;
}

int n, k, d;
vector<Person> ps;

int cnts[31];
int cnt;
int eff;

bool including(int s, int index) {
  return (s & (1 << index)) > 0;
}

void count(int s) {
  ++cnt;
  for (int i = 0; i < 31; i++) {
    if (including(s, i)) {
      ++cnts[i];
    }
  }
  eff = 0;
  for (int i = 0; i < 31; i++) {
    if (cnts[i] > 0 && cnts[i] != cnt) ++eff;
  }
}

void discount(int s) {
  --cnt;
  for (int i = 0; i < 31; i++) {
    if (including(s, i)) {
      --cnts[i];
      if (cnts[i] == 0) --eff;
    } else {
      if (cnts[i] == cnt) --eff;
    }
  }
}

int main(void)
{
  scanf("%d%d%d", &n, &k, &d);
  ps.resize(n);
  for (int i = 0; i < n; i++) ps[i].get_input();
  sort(ps.begin(), ps.end());
  
  int start = 0, end = 0;
  int res = 0;
  while (start < n) {
    while (ps[end].skill <= ps[start].skill + d && end < n) {
      count(ps[end++].algos);
    }
    // printf("%d, %d => %d\n", start, end, eff);
    res = max(res, eff * (end - start));
    discount(ps[start++].algos);
  }
  printf("%d\n", res);
}
