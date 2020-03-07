#include <cstdio>
#include <vector>
using namespace std;

typedef long long lld;

class SegmentTree {
  lld value[600020]; // over 2*2^{ceil(log2(x))} - 1
  lld lazy [600020];
  void _update_lazy(int n_begin, int n_end, int index) {
    if (lazy[index] == 0) return;
    int n_size = n_end - n_begin;
    if (n_size >= 2) {
      lazy[index << 1] += lazy[index];
      lazy[(index << 1) + 1] += lazy[index];
    }
    value[index] += lazy[index] * n_size;
    lazy[index] = 0;
  }
  void _add_range(int begin, int end, lld v, int n_begin, int n_end, int index) {
    #ifdef LOG_DFS
      printf("  _add(%d, %d, %d, %d, %d, %d)\n", begin, end, v, n_begin, n_end, index);
    #endif
    _update_lazy(n_begin, n_end, index);

    if (n_end <= begin || end <= n_begin) return; // 서로소
    if (begin <= n_begin && n_end <= end) { // 포함
      int n_size = n_end - n_begin;
      value[index] += v * n_size;
      if (n_size >= 2) {
        lazy[index << 1] += v;
        lazy[(index << 1) + 1] += v;
      }
      return;
    }
    int n_mid = (n_begin + n_end) >> 1;
    _add_range(begin, end, v, n_begin, n_mid, index << 1);
    _add_range(begin, end, v, n_mid, n_end, (index << 1) + 1);
    value[index] = value[index << 1] + value[(index << 1) + 1];
  }
  lld _get_range(int begin, int end, int n_begin, int n_end, int index) {
    #ifdef LOG_DFS
      printf("  _get(%d, %d, %d, %d, %d)\n", begin, end, n_begin, n_end, index);
    #endif
    _update_lazy(n_begin, n_end, index);
    
    if (n_end <= begin || end <= n_begin) return 0; // 서로소
    if (begin <= n_begin && n_end <= end) return value[index]; // 포함
    int n_mid = (n_begin + n_end) >> 1;
    return _get_range(begin, end, n_begin, n_mid, index << 1)
         + _get_range(begin, end, n_mid, n_end, (index << 1) + 1);
  }
public:
  int size = 200001;
  void add_range(int begin, int end, lld v) {
    #ifdef LOG_DFS
      printf("add(%d, %d, %d)\n", begin, end, v);
    #endif
    _add_range(begin, end, v, 0, size, 1);
  }
  lld get_range(int begin, int end) {
    #ifdef LOG_DFS
      printf("get(%d, %d)\n", begin, end);
    #endif
    return _get_range(begin, end, 0, size, 1);
  }
};
SegmentTree tree;

int n, c, q;
vector<int> adj[200001];
int weight[200001];
int parent[200001];
int depth[200001];
int heavy_child[200001];
int chain[200001]; int chain_index;
int chain_size[200001];
int chain_top[200001];
int num[200001]; int num_index;

void make_tree(int curr, int prev) {
  parent[curr] = prev;
  weight[curr] = 1;
  for (int child: adj[curr]) {
    if (child == prev) continue;
    depth[child] = depth[curr] + 1;
    make_tree(child, curr);
    weight[curr] += weight[child];
    if (heavy_child[curr] == 0 || weight[heavy_child[curr]] < weight[child]) {
      heavy_child[curr] = child;
    }
  }
}

void hld(int curr, int prev) {
  chain[curr] = chain_index;
  num[curr] = num_index++;
  if (chain_size[chain_index] == 0) {
    chain_top[chain_index] = curr;
  }
  chain_size[chain_index]++;
  if (heavy_child[curr]) {
    hld(heavy_child[curr], curr);
  }
  for (int child: adj[curr]) {
    if (child == heavy_child[curr] || child == prev) {
      continue;
    }
    chain_index++;
    hld(child, curr);
  }
}

void fill_water(int index) {
  while (index) {
    int top = chain_top[chain[index]];
    tree.add_range(num[top], num[index] + 1, 1);
    index = parent[top];
  }
}

lld get_water(int index) {
  return (lld)depth[index] * tree.get_range(num[index], num[index] + 1);
}

int main(void)
{
  scanf("%d%d", &n, &c);
  for (int i = 1; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  depth[c] = 1;
  make_tree(c, 0);
  hld(c, 0);
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int cmd, index; scanf("%d%d", &cmd, &index);
    if (cmd == 1) {
      fill_water(index);
    } else {
      printf("%lld\n", get_water(index));
    }
  }
}
