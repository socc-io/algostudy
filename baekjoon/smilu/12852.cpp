#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int start;
int bt[1000001];
int visit[1000001];

int main(void)
{
  scanf("%d", &start); 
  queue<int> q;
  q.push(start);
  bool found = false;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    int vs[3]; int vsn = 0;
    if (u % 3 == 0) vs[vsn++] = u / 3;
    if ((u & 1) == 0) vs[vsn++] = u >> 1;
    vs[vsn++] = u - 1;
    for (int vi = 0; vi < vsn; vi++) {
      int v = vs[vi];
      if (visit[v]) continue;
      bt[v] = u;
      visit[v] = true;
      if (v == 1) {
        found = true;
        break;
      }
      q.push(v);
    }
    if (found) break;
  }
  vector<int> tape;
  int cur = 1;
  tape.push_back(1);
  while(bt[cur]) {
    cur = bt[cur];
    tape.push_back(cur);
  }
  reverse(tape.begin(), tape.end());
  printf("%lu\n", tape.size()-1);
  for (int i = 0; i < tape.size(); i++) {
    printf("%d ", tape[i]);
  }
}