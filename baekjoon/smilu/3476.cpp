#include <bits/stdc++.h>
using namespace std;

string get_line() {
  string ret;
  char ch;
  while ((ch = cin.get()) != '\n' && ch != -1) {
    ret.push_back(ch);
  }
  if (ret.size() == 0) return get_line();
  return ret;
}

bool check_blacklist(const string &s, const vector<string> &blacklist) {
  for (const string &black: blacklist) {
    if (s.compare(black) == 0) return false;
  }
  return true;
}

bool is_neg_word(const string &s) {
  return !check_blacklist(s, {
    "don't",
    "doesn't"
  });
}

bool is_noun(const string &s) {
  return check_blacklist(s, {
    "what",
    "who",
    "does",
    "do",
  });
}

bool is_plural(const string &s) {
  return !check_blacklist(s, {
    "I",
    "you",
  });
}

bool is_article(const string &s) {
  return !check_blacklist(s, {
    "a",
    "to",
  });
}

void trim(string &s) {
  if (s.size() > 0 && (s.back() == '?' || s.back() == '.')) {
    s.pop_back();
  }
}

class Dictionary: map<string, int> {
  vector<string> words;
  int _add(const string &word) {
    insert({word, words.size()});
    words.push_back(word);
    return words.size() - 1;
  }
public:
  void clear() {
    words.clear();
  }
  int get_number(const string &word) {
    auto it = find(word);
    if (it == end()) return _add(word);
    return it->second;
  }
  string get_word(int index) {
    if (index >= words.size()) return "";
    return words[index];
  }
};

struct Fact {
  int t;
  int s, v, o;
  bool neg;
  Fact() {}
  Fact(int t, int s, bool neg, int v, int o = -1):
    t(t),s(s),v(v),o(o),neg(neg) {}
  Fact inverse() {
    return Fact(t, s, !neg, v, o);
  }
  bool operator<(const Fact &f) const { return t < f.t; }
};

class Machine {
  Dictionary dict;
  vector<Fact> facts;
  multimap<int, int> by_subj;
  multimap<int, int> by_verb;
  multimap<pair<int,int>, int> by_verb_obj;
  map<tuple<int,int,int>,int> by_all;
  int n_everybody;
  int n_nobody;
  int n_i;
  int n_you;
  bool abroad;
  bool _check_abroad(int sn, int vn, int on, bool neg) {
    if (sn == n_everybody) {
      if (neg) return _check_abroad(n_nobody, vn, on, false);
      auto fs = _query_verb(vn, on);
      for (auto f: fs) {
        if (f.neg) return true;
        if (f.s == n_nobody && !f.neg) return true;
      }
    }
    if (sn == n_nobody) {
      if (neg) return _check_abroad(n_everybody, vn, on, false);
      auto fs = _query_verb(vn, on);
      for (auto f: fs) {
        if (!f.neg) return true;
        if (f.s == n_everybody && !f.neg) return true;
      }
    }
    auto fs = _query_subj_verb(sn, vn, on);
    for (auto f: fs) if (f.neg != neg) return true;
    fs = _query_subj_verb(n_everybody, vn, on);
    for (auto f: fs) if (f.neg != neg) return true;
    fs = _query_subj_verb(n_nobody, vn, on);
    for (auto f: fs) if (f.neg == neg) return true;
    return false;
  }
  void _insert(int sn, int vn, int on, bool neg) {
    if (abroad) return;
    int fi = facts.size();
    if (_check_abroad(sn, vn, on, neg)) {
      abroad = true;
      return;
    }
    facts.push_back(Fact(fi, sn, neg, vn, on));
    by_subj.insert({sn, fi});
    by_verb.insert({vn, fi});
    if (on != -1) {
      by_verb_obj.insert({{vn, on}, fi});
    }
    by_all.insert({{sn, vn, on}, fi});
  }
  template <class T>
  vector<Fact> _query_index(const multimap<T,int> &index, T key) {
    auto lo = index.lower_bound(key);
    auto up = index.upper_bound(key);
    vector<Fact> ret;
    for (auto it = lo; it != up; it++) {
      ret.push_back(facts[it->second]);
    }
    return ret;
  }
  vector<Fact> _query_subj(int sn) {
    auto ret = _query_index(by_subj, sn);
    if (sn != n_everybody && sn != n_nobody) {
      auto no = _query_subj(n_nobody);
      for (auto &f: no) ret.push_back(f.inverse());
      auto ev = _query_subj(n_everybody);
      for (auto &f: ev) ret.push_back(f);
    }
    return ret;
  }
  vector<Fact> _query_verb(int vn, int on = -1) {
    if (on == -1) return _query_index(by_verb, vn);
    return _query_index(by_verb_obj, {vn, on});
  }
  vector<Fact> _query_subj_verb(int sn, int vn, int on = -1) {
    vector<Fact> ret;
    auto it = by_all.find({sn, vn, on});
    if (it != by_all.end()) ret.push_back(facts[it->second]);
    it = by_all.find({n_everybody, vn, on});
    if (it != by_all.end()) ret.push_back(facts[it->second]);
    it = by_all.find({n_nobody, vn, on});
    if (it != by_all.end()) ret.push_back(facts[it->second].inverse());
    return ret;
  }
  void filter_neg(vector<Fact> &facts) {
    int n = 0;
    for (int i = 0; i < facts.size(); i++) {
      if (facts[i].neg) continue;
      facts[n++] = facts[i];
    }
    facts.resize(n);
  }
  int including_everybody(const vector<Fact> &facts) {
    for (int i = 0; i < facts.size(); i++) {
      if (facts[i].s == n_everybody) return i;
    }
    return facts.size();
  }
public:
  void clear() {
    dict.clear();
    facts.clear();
  }
  void insert(const string &s, const string &v, bool neg) {
    // cout << "S: " << s << ", V: " << v << ", neg: " << neg << '\n';
    _insert(
      dict.get_number(s),
      dict.get_number(v),
      -1, neg
    );
  }
  void insert(const string &s, const string &v, const string &o, bool neg) {
    // cout << "S: " << s << ", V: " << v << ", O: " << o << ", neg: " << neg << '\n';
    _insert(
      dict.get_number(s),
      dict.get_number(v),
      dict.get_number(o),
      neg
    );
  }
  int get_number(const string &s) {
    return dict.get_number(s);
  }
  string replace_you_i(const string &s) {
    if (s.compare("I") == 0) return "you";
    if (s.compare("you") == 0) return "I";
    return s;
  }
  string query_subj(const string &s) { // what
    if (abroad) return "I am abroad.";
    int sn = get_number(s);
    vector<Fact> facts = _query_subj(sn);
    if (facts.size() == 0) return "I don't know.";
    sort(facts.begin(), facts.end());
    bool plural = is_plural(s);
    const string &neg_word = plural ? "don't " : "doesn't ";
    string ret = replace_you_i(s) + ' ';
    for (int i = 0; i < facts.size(); i++) {
      const Fact &f = facts[i];
      bool first = (i == 0);
      bool last = (i == facts.size() - 1);
      if (!first) ret += ", ";
      if (!first && last) ret += "and ";
      if (f.neg) ret += neg_word;
      ret += dict.get_word(f.v);
      if (!plural && !f.neg) ret += 's';
      if (f.o != -1) ret += " " + dict.get_word(f.o);
    }
    ret += '.';
    return ret;
  }
  string query_verb(const string &v, const string &o = "") { // who
    if (abroad) return "I am abroad.";
    int vn = get_number(v);
    int on = o.size() ? get_number(o) : -1;
    vector<Fact> facts = _query_verb(vn, on);
    filter_neg(facts);
    if (facts.size() == 0) {
      return "I don't know.";
    }
    sort(facts.begin(), facts.end());

    int ei = including_everybody(facts);
    if (ei < facts.size()) {
      facts[0] = facts[ei];
      facts.resize(1);
    }

    string ret;
    for (int i = 0; i < facts.size(); i++) {
      const Fact &f = facts[i];
      bool first = (i == 0);
      bool last = (i == facts.size() - 1);
      if (!first) {
        if (!last) ret += ", ";
        else ret += " and ";
      }
      ret += replace_you_i(dict.get_word(f.s));
    }
    ret += ' ';
    ret += v;

    if (facts.size() == 1) {
      const string &s = dict.get_word(facts[0].s);
      if (!is_plural(s)) ret += 's';
    }

    if (on != -1) {
      ret += ' ';
      ret += replace_you_i(o);
    }

    ret += '.';
    return ret;
  }
  string query_subj_verb(const string &s, const string &v, const string &o = "") { // does
    if (abroad) return "I am abroad.";
    int sn = get_number(s);
    int vn = get_number(v);
    int on = o.size() ? get_number(o) : -1;
    vector<Fact> facts = _query_subj_verb(sn, vn, on);
    if (facts.size() == 0) return "maybe.";
    string ret;
    const Fact f = facts[0];
    bool plural = is_plural(s);
    ret += (f.neg ? "no, " : "yes, ");
    ret += replace_you_i(s) + ' ';
    if (f.neg) ret += plural ? "don't " : "doesn't ";
    ret += v;
    if (!f.neg && !plural) ret += 's';
    if (on != -1) ret += " " + replace_you_i(o);
    ret += '.';
    return ret;
  }
  Machine() {
    n_everybody = dict.get_number("everybody");
    n_nobody = dict.get_number("nobody");
    n_i = dict.get_number("I");
    n_you = dict.get_number("you");
    abroad = false;
  }
};

pair<vector<string>, bool> split_words(const string &line) {
  // cout << "line: " << line << '\n';
  vector<string> ws;
  int sb = 0, se = 0;
  for (se = 0; se < line.size(); se++) {
    if (line[se] != ' ') continue;
    ws.push_back(line.substr(sb, se-sb));
    // cout << "  word: " << ws.back() << '\n';
    sb = se+1;
  }
  ws.push_back(line.substr(sb, se-sb));
  trim(ws.back());
  // cout << "  word: " << ws.back() << '\n';
  return {ws, line.back() == '?'};
}

vector<string> limit_size(const vector<string> &ws, int lim) {
  vector<string> ret;
  for (int i = 0; i < ws.size(); i++) {
    if (ret.size() >= lim) {
      ret.back() += " " + ws[i];
    } else {
      ret.push_back(ws[i]);
    }
  }
  return ret;
}

vector<string> combine_objects(const vector<string> &ws, bool is_query) {
  if (ws[0].compare("what") == 0 && is_query) {
    return ws;
  } else if (ws[0].compare("who") == 0 && is_query) {
    return limit_size(ws, 3);
  } else if (!check_blacklist(ws[0], {"do", "does"}) && is_query) {
    return limit_size(ws, 4);
  }
  if (is_neg_word(ws[1])) return limit_size(ws, 4);
  return limit_size(ws, 3);
}

void update(Machine &m, vector<string> &ws) {
  const string &subject = ws[0];
  int neg = is_neg_word(ws[1]);
  string &verb = ws[neg+1];
  if (!is_plural(subject) && !neg) verb.pop_back(); // remove 's'
  if (ws.size() >= neg+3) { // S V O
    const string &object = ws[neg+2];
    m.insert(subject, verb, object, neg);
  } else {
    m.insert(subject, verb, neg);
  }
}

void query_subj(Machine &m, const vector<string> &ws) {
  cout << m.query_subj(ws[2]) << '\n';
}

void query_verb(Machine &m, const vector<string> &ws) {
  string verb = ws[1];
  verb.pop_back();
  const string &object = ws.size() >= 3 ? ws[2] : "";
  cout << m.query_verb(verb, object) << '\n';
}

void query_subj_verb(Machine &m, const vector<string> &ws) {
  const string &subject = ws[1];
  const string &verb = ws[2];
  const string &object = ws.size() >= 4 ? ws[3] : "";
  cout << m.query_subj_verb(subject, verb, object) << '\n';
}

void query(Machine &m, const vector<string> &ws) {
  if (ws[0].compare("what") == 0) {
    query_subj(m, ws);
  } else if (ws[0].compare("who") == 0) {
    query_verb(m, ws);
  } else {
    query_subj_verb(m, ws);
  }
  cout << '\n';
}

void process(Machine &m, const string &line) {
  // cout << "Process: " << line << "\n";
  pair<vector<string>,bool> res = split_words(line);
  bool is_query = res.second; 
  vector<string> words = combine_objects(res.first, is_query);
  if (line.size() == 0 || words.size() == 0) return;
  if (!is_query) {
    update(m, words);
  } else {
    cout << line << '\n';
    query(m, words);
  }
}

void solve() {
  Machine m;
  while (1) {
    string line = get_line();
    if (line.back() == '!') {
      cout << line << "\n";
      break;
    }
    process(m, line);
  }
}

int main(void) {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  for (int i = 1; i <= t; i++) {
    if (i > 1) cout << '\n';
    cout << "Dialogue #" << i << ":\n";
    solve();
  }
  return 0;
}
