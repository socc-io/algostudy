#include <bits/stdc++.h>
using namespace std;

struct Node {
  int _next[26];
  int dist;
  bool terminal;
  static Node* alloc();
  int nid();
  Node* get(int nid);
  void clear() {
    memset(_next, 0xFF, sizeof(_next));
    dist = 0;
    terminal = false;
  }
  Node* grow(const string &s, int begin = 0) {
    if (begin >= s.size()) {
      terminal = true;
      return this;
    }
    int n_index = (int)(s[begin] - 'a');
    if (_next[n_index] == -1) {
      _next[n_index] = alloc()->nid();
    }
    return get(_next[n_index])->grow(s, begin + 1);
  }
  int count_next() {
    int ret = 0;
    for (int i = 0; i < 26; i++) ret += (_next[i] != -1);
    return ret;
  }
  void update_dist(bool root = true) {
    if (root) dist = 0;
    int c_cnt = count_next();
    if (c_cnt == 0) return;
    int inc = (c_cnt != 1) || terminal || root;
    for (int i = 0; i < 26; i++) {
      if (_next[i] == -1) continue;
      get(_next[i])->dist = dist + inc;
      get(_next[i])->update_dist(false);
    }
  }
};

Node pool_node[1000010];
int pool_node_piv;

Node* Node::alloc() {
  Node* ret = pool_node + (pool_node_piv++);
  ret->clear();
  return ret;
}

Node* Node::get(int nid) { return pool_node + nid; }
int Node::nid() { return (int)(this - pool_node); }

double solve(int n) {
  pool_node_piv = 0;
  Node* root = Node::alloc();
  vector<Node*> terminals(n);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    terminals[i] = root->grow(s);
  }
  root->update_dist();
  long long sum_dist = 0; 
  for (Node* t: terminals) sum_dist += t->dist;
  double avg_dist = (double)sum_dist / (double)n;
  return avg_dist;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(2);
  while (!cin.eof()) {
    int n; cin >> n;
    if (cin.eof()) break;
    cout << solve(n) << '\n';
  }
}