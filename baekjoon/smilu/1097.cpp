#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int n, k;
string words[8];
int ci[8];
bool cc[8];
int cnt;

vi get_pi(const string &s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

int kmp(const string &s, const string &q) {
  int ans = 0;
  const vi pi = get_pi(q);
  int n = s.size(), m = q.size(), j = 0;
  for (int i = 0; i < n; i++) {
    while (j > 0 && s[i] != q[j]) j = pi[j-1];
    if (s[i] == q[j]) {
      if (j == m-1) {
        ++ans;
        j = pi[j];
      } else {
        j++;
      }
    }
  }
  return ans;
}

string get_word() {
  string res;
  for (int i = 0; i < n; i++) res += words[ci[i]];
  return res;
}

bool check() {
  const string word = get_word();
  const string d_word = word + word;
  const bool res = kmp(d_word, word) - 1 == k;
  // if (res) cout << word << '\n';
  return res;
}

void dfs(int index) {
  if (index >= n) {
    cnt += check();
    return;
  }
  const int next_index = index + 1;
  for (int i = 1; i < n; i++) {
    if (cc[i]) continue;
    ci[index] = i;
    cc[i] = true;
    dfs(next_index);
    cc[i] = false;
  }
}

int solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> words[i];ㅈ
  cin >> k;
  dfs(1);
  return cnt * n;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve() << '\n';
}
