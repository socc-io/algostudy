#include <cstdio>
#include <map>
using namespace std;

struct Node {
  Node* v[2];
  Node* p;
  int depth;
  int value;
  Node(Node* p, int depth): p(p), depth(depth) {
    v[0] = NULL;
    v[1] = NULL;
  }
  bool empty() const {
    return v[0] == NULL && v[1] == NULL;
  }
  Node* build(int x) {
    if (depth == 31) {
      value = x;
      return this;
    }
    int idx = (x & (1 << (30-depth))) > 0;
    if (!v[idx]) v[idx] = new Node(this, depth + 1);
    return v[idx]->build(x);
  }
  void remove(int x) {
    if (depth == 31) return;
    int idx = (x & (1 << (30-depth))) > 0;
    v[idx]->remove(x);
    if (v[idx]->empty()) {
      delete v[idx];
      v[idx] = NULL;
    }
  }
  int query(int x) {
    if (depth == 31) return value;
    int idx = (x & (1 << (30-depth))) > 0;
    if (v[idx]) {
      int res = v[idx]->query(x);
      if (res != -1) return res;
    }
    int res = v[1-idx]->query(x);
    if (res != -1) return res;
    return -1;
  }
};

int main(void)
{
  int m;
  Node rt(NULL, 0);
  map<int, int> cnt;
  rt.build(0);
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int cmd, x; scanf("%d%d", &cmd, &x);
    if (cmd == 1) {
      cnt[x]++;
      if (cnt[x] == 1) rt.build(x);
    } else if (cmd == 2) {
      cnt[x]--;
      if (cnt[x] == 0) rt.remove(x);
    } else {
      printf("%d\n", rt.query(~x) ^ x);
    }
  }
}
