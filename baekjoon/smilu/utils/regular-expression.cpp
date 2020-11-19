#include <bits/stdc++.h>
using namespace std;

struct Edge {
  char ch;
  int dst;
  Edge(char ch, int dst): ch(ch), dst(dst) {}
};

struct Node {
  bool fin = false;
  vector<Edge> edges;
  Node() {}
};

class Solution {
  vector<Node> nodes;
  void build_nodes(const string &p) {
    nodes.clear();
    nodes.push_back(Node());
    int n = 0;
    for (int i = 0; i < p.size(); i++) {
      char ch = p[i];
      nodes.push_back(Node());
      ++n;
      if (i + 1 < p.size() && p[i + 1] == '*') {
        nodes[n - 1].edges.push_back(Edge(0, n));
        nodes[n].edges.push_back(Edge(ch, n));
        ++i;
      } else {
        nodes[n - 1].edges.push_back(Edge(ch, n));
      }
    }
    nodes[n].fin = true;
    for (int i = n-1; i >= 0; i--) {
      for (auto e: nodes[i].edges) {
        if (e.ch != 0) continue;
        if (nodes[e.dst].fin) {
          nodes[i].fin = true;
          break;
        }
      }
    }
  }
  bool explore(int node, int pos, const string &s) {
    if (pos >= s.size()) {
      return nodes[node].fin;
    }
    for (auto e: nodes[node].edges) {
      if (e.ch == 0) {
        if (explore(e.dst, pos, s)) return true;
      } else {
        char ch = s[pos]; 
        if (ch == e.ch || e.ch == '.') {
          if (explore(e.dst, pos + 1, s)) return true;
        }
      }
    }
    return false;
  }
public:
  bool isMatch(string s, string p) {
    build_nodes(p);
    return explore(0, 0, s);
  }
};
