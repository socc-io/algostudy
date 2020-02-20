#include <cstdio>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

int backtrace[10000];
int backtrace_type[10000];

const char* ttoc = "DSLR";

int d(int x) {
  return (x << 1) % 10000;
}
int s(int x) {
  return (x + 9999) % 10000;
}
int l(int x) {
  int t = x / 1000;
  return (x * 10 + t) % 10000;
}
int r(int x) {
  int t = x % 10;
  return (x / 10 + t * 1000);
}

typedef int (*converter)(int);

converter convs[] = {d, s, l, r};

void bfs(int start, int target) {
  queue<int> q;
  q.push(start);
  while(!q.empty()) {
    int u = q.front();
    if (u == target) return;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int val = convs[i](u);
      if (backtrace[val] == -1) {
        backtrace[val] = u;
        backtrace_type[val] = i;
        q.push(val);
      }
    }
  }
}

void solve() {
  int a, b;
  scanf("%d%d", &a, &b);
  for (int i = 0; i < 10000; i++) backtrace[i] = -1;
  bfs(a, b);

  string res;
  int cur = b;
  while(cur != a) {
    res.push_back(ttoc[backtrace_type[cur]]);
    cur = backtrace[cur];
  }
  reverse(res.begin(), res.end());
  printf("%s\n", res.c_str());
}

int main(void)
{
  int t;
  scanf("%d", &t);
  while(t--) solve();
}