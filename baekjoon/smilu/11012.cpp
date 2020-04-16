#include <cstdio>
using namespace std;

#define MAX_X 100001
#define MAX_Y 100001

struct SegY {
  int value;
  SegY *child[2];
  static SegY* get_node_y();
  void add(int begin, int end, int y, int alpha) {
    value += alpha;
    if (begin + 1 == end) return;
    int mid = (begin + end) >> 1;
    if (y < mid) {
      if (child[0] == NULL) child[0] = get_node_y();
      child[0]->add(begin, mid, y, alpha);
    } else {
      if (child[1] == NULL) child[1] = get_node_y();
      child[1]->add(mid, end, y, alpha);
    }
  }
  int get(int begin, int end, int from, int to) {
    if (to <= begin || from >= end) return 0;
    if (from <= begin && end <= to) return value;
    int mid = (begin + end) >> 1;
    int lr = child[0] == NULL ? 0 : child[0]->get(begin, mid, from, to);
    int rr = child[1] == NULL ? 0 : child[1]->get(mid, end, from, to);
    return lr + rr;
  }
};

struct SegX {
  SegY *value;
  SegX *child[2];
  static SegX* get_node_x();
  void add(int begin, int end, int x, int y, int alpha) {
    value->add(0, MAX_Y, y, alpha);
    if (begin + 1 == end) return;
    int mid = (begin + end) >> 1;
    if (x < mid) {
      if (child[0] == NULL) child[0] = get_node_x();
      child[0]->add(begin, mid, x, y, alpha);
    } else {
      if (child[1] == NULL) child[1] = get_node_x();
      child[1]->add(mid, end, x, y, alpha);
    }
  }
  int get(int begin, int end, int from, int to, int y_from, int y_to) {
    if (to <= begin || from >= end) return 0;
    if (from <= begin && end <= to) return value->get(0, MAX_Y, y_from, y_to);
    int mid = (begin + end) >> 1;
    int lr = child[0] == NULL ? 0 : child[0]->get(begin, mid, from, to, y_from, y_to);
    int rr = child[1] == NULL ? 0 : child[1]->get(mid, end, from, to, y_from, y_to);
    return lr + rr;
  }
};

SegY pool_y[4000000];
SegX pool_x[400000];
int pyi, pxi;

SegY* SegY::get_node_y() {
  SegY *res = pool_y + (pyi++);
  res->value = 0;
  res->child[0] = NULL;
  res->child[1] = NULL;
  return res;
}

SegX* SegX::get_node_x() {
  SegX *res = pool_x + (pxi++);
  res->value = SegY::get_node_y();
  res->child[0] = NULL;
  res->child[1] = NULL;
  return res;
}

void solve() {
  pxi = 0;
  pyi = 0;
  SegX *root = SegX::get_node_x();

  int n, m, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    root->add(0, MAX_X, x, y, 1);
  }
  for (int i = 0; i < m; i++) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
    ans += root->get(0, MAX_X, x1, x2+1, y1, y2+1);
  }
  printf("%d\n", ans);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
