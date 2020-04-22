#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

int n;
string s;
vector<string> words;
vector<bool> is_num;
vector<int> cons; // index of string representing constant value
vector<int> pres;
map<string, int> w_indices;
set<pii> pne;
vector<vector<int>> eq, ne;

inline bool isdigit(char ch) {
  return '0' <= ch && ch <= '9';
}

bool check_num(const string &s) {
  for (char ch: s) {
    if (ch == '-' || ('0' <= ch && ch <= '9')) return true;
  }
  return false;
}

int get_word(int begin, int end) {
  string w = s.substr(begin, end - begin);
  auto it = w_indices.find(w);
  if (it == w_indices.end()) {
    int ret = words.size();
    w_indices[w] = ret;
    words.push_back(w);
    is_num.push_back(check_num(w));
    eq.push_back(vector<int>());
    ne.push_back(vector<int>());
    return ret;
  }
  return it->second;
}

void register_phrase(int begin, int end) {
  int k = begin; while (s[k] != '=' && s[k] != '!') k++;
  int w0 = get_word(begin, k);
  int w1 = get_word(k+2, end);

  if (s[k] == '=') {
    eq[w0].push_back(w1);
    eq[w1].push_back(w0);
    // printf("reg: %d == %d\n", w0, w1);
  } else {
    ne[w0].push_back(w1);
    ne[w1].push_back(w0);
    // printf("reg: %d != %d\n", w0, w1);
  }
}

void parse_string() {
  int begin = 0;
  for (int end = 1; end <= s.size(); end++) {
    bool end_check = (end + 1 < s.size()) && (s[end] == '&') && (s[end+1] == '&');
    if (end != s.size() && !end_check) continue;
    register_phrase(begin, end);
    begin = end = end+2;
  }
}

int find_shortest(int root) {
  int ret = root;
  int ret_size = words[root].size();
  queue<int> q;
  vector<bool> visit(n, false);

  visit[root] = true;
  q.push(root);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    int u_size = words[u].size();
    if (u_size < ret_size) {
      ret = u;
      ret_size = u_size;
    }
    for (int v: eq[u]) {
      if (visit[v]) continue;
      visit[v] = true;
      q.push(v);
    }
  }

  return ret;
}

void set_president(int u, int pr) {
  pres[u] = pr;
  for (int v: eq[u]) {
    if (pres[v] != -1) continue;
    set_president(v, pr);
  }
}

bool check_two_constants() {
  cons.resize(n, -1);
  for (int i = 0; i < n; i++) {
    if (!is_num[i]) continue;
    int g = pres[i];
    if (cons[g] != -1) return true;
    cons[g] = i;
  }
  return false;
}

bool check_ne_in_group() {
  for (int i = 0; i < n; i++) {
    for (int v: ne[i]) {
      if (pres[i] == pres[v]) return true;
    }
  }
  return false;
}

int main(void)
{
  cin >> s;
  parse_string();
  n = words.size();

  pres.resize(n, -1);
  for (int i = 0; i < n; i++) {
    if (pres[i] != -1) continue;
    int pr = find_shortest(i);
    set_president(i, pr);
  }

  if (check_two_constants() || check_ne_in_group()) {
    puts("1==0");
    return 0;
  }

  for (int i = 0; i < n; i++) {
    for (int v: ne[i]) {
      // printf("%d(%d) != %d(%d\n", i, pres[i], v, pres[v]);
      int a = pres[i], b = pres[v];
      if (a > b) swap(a, b);
      pne.insert({a, b});
    }
  }

  bool ap = false;
  for (int i = 0; i < n; i++) {
    if (pres[i] == i) continue;
    if (ap) cout << "&&";
    cout << words[pres[i]] << "==" << words[i];
    ap = true;
  }
  
  for (auto p: pne) {
    int a = p.first, b = p.second;
    if (cons[pres[a]] != -1 && cons[pres[b]] != -1) continue;
    if (ap) cout << "&&";
    cout << words[a] << "!=" << words[b];
    ap = true;
  }

  if (!ap) puts("1==1");
}
