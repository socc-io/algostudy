#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int TRIE_SZ = 26;

struct Trie {
  int next_ids[TRIE_SZ];
  int fail_id;
  int output;
  Trie *find(int id);
  int get();
  int id();
  Trie* next(int nid) { return find(next_ids[nid]); }
  Trie* fail() { return find(fail_id); }
  void expand(const string &s, int begin = 0) {
    if (begin >= s.size()) {
      output = (int)s.size();
      return;
    }
    int nid = s[begin] - 'a';
    if (next_ids[nid] == 0) {
      next_ids[nid] = get();
    }
    next(nid)->expand(s, begin + 1);
  }
  vector<pi> travel(const string &s) {
    vector<pi> ret;
    Trie *cur = this;
    for (int i = 0; i < s.size(); i++) {
      char ch = s[i];
      int nid = ch - 'a';
      while (cur != this && cur->next_ids[nid] == 0) {
        cur = cur->fail();
      }
      if (cur->next_ids[nid]) cur = cur->next(nid);
      if (cur->output) ret.emplace_back(i - cur->output + 1, i);
    }
    return ret;
  }
};

Trie ts[4000000];
int t_piv;

int Trie::get() { return t_piv++; }
Trie* Trie::find(int id) { return ts + id; }
int Trie::id() { return this - ts; }

void build_failure(Trie *root) {
  queue<Trie*> q;
  root->fail_id = root->id();
  q.push(root);
  while (!q.empty()) {
    Trie *u = q.front(); q.pop();
    for (int nid = 0; nid < TRIE_SZ; nid++) {
      if (u->next_ids[nid] == 0) continue;
      Trie *v = u->next(nid);
      if (u == root) {
        v->fail_id = u->id();
      } else {
        Trie *dst = u->fail();
        while (dst != root && dst->next_ids[nid] == 0) {
          dst = dst->fail();
        }
        if (dst->next_ids[nid]) dst = dst->next(nid);
        v->fail_id = dst->id();
      }
      v->output = max(v->output, v->fail()->output);
      q.push(v);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  Trie *root = ts+1;
  t_piv = 2;
  int n; cin >> n;
  string s; cin >> s;
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    string k; cin >> k;
    root->expand(k);
  }
  build_failure(root);
  auto matches = root->travel(s);
  vector<bool> chk(s.size());
  int ans = s.size();
  for (const auto &match: matches) {
    for (int i = match.first; i <= match.second; i++) {
      if (chk[i]) continue;
      chk[i] = true;
      --ans;
    }
  }
  cout << ans << '\n';
}
