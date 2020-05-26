#include <bits/stdc++.h>
using namespace std;

void print_chars(char ch, int n) {
  for (int i = 0; i < n; i++) putchar(ch);
}
void indent(int n) {
  print_chars('-', n);
}

struct Node {
  string name;
  map<string, Node*> chd;
  Node* forward(const string &s);
  void print(int depth = -1) {
    if (depth != -1) {
      indent(depth << 1);
      cout << name << '\n';
    }
    for (const auto &it: chd) {
      it.second->print(depth + 1);
    }
  }
} nodes[15000];
int node_piv;

Node* get_node(const string &name) {
  Node* ret = nodes + (node_piv++);
  ret->name = name;
  ret->chd.clear();
  return ret;
}

Node* Node::forward(const string &s) {
  auto it = chd.find(s);
  if (it == chd.end()) {
    Node* nxt = get_node(s);
    chd.insert({s, nxt});
    return nxt;
  }
  return it->second;
}

void recv_route(Node* root) {
  int n; cin >> n;
  Node* cur = root;
  for (int i = 0; i < n; i++) {
    string name; cin >> name;
    cur = cur->forward(name);
  }
}

int main(void)
{
  int n; cin >> n;
  Node* root = get_node("");
  for (int i = 0; i < n; i++) recv_route(root);
  root->print();
}
