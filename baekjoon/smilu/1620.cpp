#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

int main(void)
{
  cin.tie(NULL);
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;
  vector<string> names;
  map<string, int> keys;
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    names.push_back(s);
    keys[s] = i;
  }
  for (int i = 0; i < M; i++) {
    string s; cin >> s;
    int index;
    if (is_digit(s.c_str()[0])) { // number
      index = atoi(s.c_str()) - 1;
      cout << names[index] << '\n';
    } else { // name
      cout << keys[s] + 1 << '\n';
    }
  }
}