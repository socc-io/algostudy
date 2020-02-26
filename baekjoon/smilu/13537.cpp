#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
  vector<int> arr;
  int begin, end, size;
  node *left, *right;
};

node* build_tree(vector<int> &arr, int begin, int end) {
  node *res = new node();
  res->begin = begin;
  res->end = end;
  res->size = end - begin;
  
  if (res->size == 1) {
    res->arr.push_back(arr[begin]);
    res->left = NULL;
    res->right = NULL;
    return res;
  }
  int mid = (begin + end) / 2;
  res->left = build_tree(arr, begin, mid);
  res->right = build_tree(arr, mid, end);
  copy(res->left->arr.begin(), res->left->arr.end(), back_inserter(res->arr));
  copy(res->right->arr.begin(), res->right->arr.end(), back_inserter(res->arr));
  sort(res->arr.begin(), res->arr.end());
  return res;
}

int query(node* tree, int begin, int end, int k) {
  if (tree->end <= begin || end <= tree->begin) return 0;
  if (begin <= tree->begin && tree->end <= end) {
    auto up = upper_bound(tree->arr.begin(), tree->arr.end(), k);
    int cnt = tree->arr.end() - up;
    // printf("(%d, %d, %d): %d\n  ", begin+1, end, k, cnt);
    // for (int i = 0; i < tree->arr.size(); i++) printf("%d ", tree->arr[i]);
    return cnt;
  }
  return query(tree->left, begin, end, k) + query(tree->right, begin, end, k);
}

int main(void)
{
  int n, m;
  scanf("%d", &n);
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  node *root = build_tree(arr, 0, arr.size());

  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int begin, end, k;
    scanf("%d%d%d", &begin, &end, &k);
    --begin;
    printf("%d\n", query(root, begin, end, k));
  }
}
