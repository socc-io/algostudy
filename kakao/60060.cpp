#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string replace_char(const string &s, const char from, const char to) {
  string res(s);
  for (int i = 0; i < s.size(); i++) {
    if (res[i] == from) res[i] = to;
    else res[i] = s[i];
  }
  return res;
}

bool compare_front(const string &a, const string &b) {
  if (a.length() != b.length()) return a.length() < b.length();
  for (int i = 0; i < a.length(); i++) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

bool compare_back(const string &a, const string &b) {
  if (a.length() != b.length()) return a.length() < b.length();
  for (int i = a.length() - 1; i >= 0; i--) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

vector<int> solution(vector<string> words, vector<string> queries) {
  vector<int> ans(queries.size());

  vector<string> &words_front = words;
  vector<string> words_back(words_front);
  sort(words_front.begin(), words_front.end(), compare_front);
  sort(words_back.begin(),  words_back.end(),  compare_back);

  for (int i = 0; i < queries.size(); i++) {
    string query_begin = queries[i];
    string query_end   = replace_char(query_begin, '?', '}');

    bool back = query_begin[0] == '?';
    auto compare     = back ? compare_back       : compare_front;
    auto words_begin = back ? words_back.begin() : words_front.begin();
    auto words_end   = back ? words_back.end()   : words_front.end();
    
    ans[i] = distance(
      lower_bound(words_begin, words_end, query_begin, compare),
      upper_bound(words_begin, words_end, query_end,   compare)
    );
  }
  return ans;
}

int main() {
  vector<string> words   = {"frodo", "front", "frost", "frozen", "frame", "kakao"};
  vector<string> queries = {"fro??", "????o", "fr???", "fro???", "pro?"};
  auto ans = solution(words, queries);

  ostream_iterator<int> out_it(cout, ", ");
  copy(ans.begin(), ans.end(), out_it);
}
