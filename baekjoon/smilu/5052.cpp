#include <bits/stdc++.h>
using namespace std;

struct Node {
  char ch;
  Node* next[10];
  bool terminal;
  void progress(const char* str);
} nodes[100010];
int node_piv;

Node* next_node(char ch = 0) {
  Node* ret = nodes + node_piv;
  ret->ch = ch;
  ret->terminal = false;
  memset(ret->next, 0x00, sizeof(Node*)*10);
  ++node_piv;
  return ret;
}

void Node::progress(const char* str) {
  if (str[0] == 0) {
    terminal = true;
    return;
  }
  int n_idx = str[0] - '0';
  if (next[n_idx] == 0) {
    next[n_idx] = next_node(str[0]);
  }
  next[n_idx]->progress(str + 1);
}

bool check_trie(Node* cur) {
  if (cur == 0) return false;
  if (cur->terminal) {
    for (int i = 0; i < 10; i++) {
      if (cur->next[i] != 0) return true;
    }
    return false;
  }
  for (int i = 0; i < 10; i++) {
    if (check_trie(cur->next[i])) return true;
  }
  return false;
}

void solve() {
  char str[11];
  int n; scanf("%d", &n);

  node_piv = 0;
  Node* root = next_node();

  for (int i = 0; i < n; i++) {
    scanf("%s", str);
    root->progress(str);
  }

  puts(check_trie(root) ? "NO" : "YES");
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
