#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = 1000000001ll;

int n, m;

class Dictionary: map<string, int> {
  vector<string> words;
  int cnt = 0;
  int add(const string &s) {
    insert(make_pair(s, cnt++));
    words.push_back(s);
    return cnt - 1;
  }
public:
  int get(const string &s) {
    auto it = find(s);
    if (it == end()) return add(s);
    return it->second;
  }
  string get(const int index) const { return words[index]; }
} dict;

bool lck[1111];
bool comp[1111];
ll cost_map[1111];
vector<vector<pair<int, ll>>> ings_maps[1111];

string getword(const string &line, const int begin) {
  int end = begin;
  while (end < line.size()) {
    const char ch = line[end];
    if (ch < 'A' || ch > 'Z') break;
    ++end;
  }
  return line.substr(begin, end - begin);
}

ll getcost(const int ni) {
  if (lck[ni]) {
    return comp[ni] ? cost_map[ni] : inf;
  }
  lck[ni] = true;
  if (cost_map[ni] == 0x3f3f3f3f3f3f3f3f && ings_maps[ni].empty()) throw -1;
  ll cost = min(inf, cost_map[ni]);
  for (const auto ings: ings_maps[ni]) {
    ll l_cost = 0;
    for (const auto ing: ings) {
      l_cost += getcost(ing.first) * ing.second;
      l_cost = min(l_cost, inf);
    }
    cost = min(cost, l_cost);
  }
  comp[ni] = true;
  cost_map[ni] = cost;
  // cout << dict.get(ni) << ": " << cost << "\n";
  return cost;
}

int main() {
  memset(cost_map, 0x3f, sizeof(cost_map));
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string name; cin >> name;
    const int ni = dict.get(name);
    ll cost; cin >> cost;
    cost_map[ni] = min(inf, cost);
  }
  for (int i = 0; i < m; i++) {
    string line; cin >> line;
    const string name = getword(line, 0);
    vector<pair<int, ll>> ings;
    int cur = name.size() + 1;
    while (cur < line.size()) {
      const ll num = line[cur] - '0';
      const string ing = getword(line, cur + 1);
      ings.emplace_back(dict.get(ing), num);
      cur += ing.size() + 2;
    }
    ings_maps[dict.get(name)].push_back(ings);
  }
  try {
    cout << getcost(dict.get("LOVE"));
  } catch (const int n) {
    cout << n;
  }
}
