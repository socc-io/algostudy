#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

typedef map<int,int> dict;

int n, k;
int ws[100];
int vs[100];

dict m[2];

void update(dict* d, int key, int value) {
  if (key > k) return;
  if (d->find(key) == d->end()) {
    (*d)[key] = value;
  } else {
    if ((*d)[key] < value) (*d)[key] = value;
  }
}

int main(void)
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", ws+i, vs+i);
  }
  dict* x = m;
  dict* y = m+1;
  for (int i = 0; i < n; i++) {
    update(y, ws[i], vs[i]);
    for (auto it = x->begin(); it != x->end(); it++) {
      int w = it->first;
      int v = it->second;
      update(y, w, v);
      update(y, w + ws[i], v + vs[i]);
    }
    x->clear();
    swap(x, y);
  }
  int max = 0;
  for (auto it = x->begin(); it != x->end(); it++) {
    if (it->second > max) max = it->second;
  }
  printf("%d", max);
}