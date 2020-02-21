#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

#define INF 0x7FFFFFF0

int n, m;
int ms[100];
int cs[100];

map<int, int> A, B;

void update(map<int,int> *m, int key, int value) {
  auto it = m->find(key);
  if (it == m->end()) m->insert(make_pair(key, value));
  else {
    if (value > it->second) it->second = value;
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &ms[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &cs[i]);
  }

  A[0] = 0;
  map<int,int> *a = &A, *b = &B;
  for (int i = 0; i < n; i++) {
    for (auto ai = a->begin(); ai != a->end(); ai++) {
      int cc = ai->first;
      int cm = ai->second;
      update(b, cc, cm);
      update(b, cc+cs[i], cm+ms[i]);
    }
    a->clear();
    swap(a, b);
  }
  int ans = INF;
  for (auto ai = a->begin(); ai != a->end(); ai++) {
    if (ai->second < m) continue;
    if (ai->first < ans) ans = ai->first;
  }
  printf("%d", ans);
}
