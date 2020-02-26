#include <cstdio>
#include <vector>
using namespace std;

typedef long long lld;
typedef vector<lld> vlld;

struct node {
  int begin;
  int end;
  int size;
  lld lazy;
  lld sum;
  node* left;
  node* right;
};

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

node* build_segment_tree(vlld &arr, int begin, int end) {
  node* res = new node();
  res->begin = begin;
  res->end = end;
  res->size = end - begin;
  res->lazy = 0;

  if (end == begin + 1) {
    res->sum = arr[begin];
    res->left = NULL;
    res->right = NULL;
    return res;
  }
  int mid = (begin + end) / 2;
  res->left = build_segment_tree(arr, begin, mid);
  res->right = build_segment_tree(arr, mid, end);
  res->sum = res->left->sum + res->right->sum;
  return res;
}

void update_lazy(node* root) {
  if (root->lazy == 0) return;
  root->sum += root->size * root->lazy;
  if (root->size > 1) {
    root->left ->lazy += root->lazy;
    root->right->lazy += root->lazy;
  }
  root->lazy = 0;
}

lld trace_sum(node* root, int begin, int end) {
  update_lazy(root);
  if (end <= root->begin || root->end <= begin) return 0;
  if (begin <= root->begin && root->end <= end) {
    // printf("sum (%d, %d): %lld\n", root->begin, root->end, root->sum);
    return root->sum;
  }
  return trace_sum(root->left, begin, end) + trace_sum(root->right, begin, end);
}

lld apply_add(node* root, int begin, int end, lld value) {
  update_lazy(root);
  if (end <= root->begin || root->end <= begin) return root->sum;
  if (begin <= root->begin && root->end <= end) {
    root->sum += root->size * value;
    if (root->size > 1) {
      root->left ->lazy += value;
      root->right->lazy += value;
    }
    return root->sum;
  }
  return root->sum = apply_add(root->left, begin, end, value) + apply_add(root->right, begin, end, value);
}

int main(void)
{
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vlld arr(n);
  for (int i = 0; i < n; i++) scanf("%lld", &arr[i]);
  node* root = build_segment_tree(arr, 0, arr.size());

  int mk = m + k;
  for (int i = 0; i < mk; i++) {
    int cmd, from, to;
    scanf("%d%d%d", &cmd, &from, &to);
    --from;
    if (cmd == 1) {
      lld value; scanf("%lld", &value);
      apply_add(root, from, to, value);
    } else  {
      printf("%lld\n", trace_sum(root, from, to));
    }
  }
}
