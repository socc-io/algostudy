/*
https://programmers.co.kr/learn/courses/30/lessons/60057
문자열 압축
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int len_int(int v) {
  if (v <= 1) return 0;
  int res = 0;
  while (v) {
    ++res;
    v /= 10;
  }
  return res;
}

int step(string s, int k) {
  int res = 0;
  string chunk = s.substr(0, k);
  while (s.size() >= k && s.substr(0, k) == chunk) {
    ++res;
    s = s.substr(k, s.size());
  }
  return res;
}

int compress_k(string s, int k) {
  int res = 0;
  while (s.size() >= k) {
    int step_size = step(s, k);
    s = s.substr(step_size * k, s.size());
    res += len_int(step_size) + k;
  }
  res += s.size();
  return res;
}

int solution(string s) {
  int res = s.size();
  int k_end = (s.size() + 1) / 2;
  for (int k = 1; k <= k_end; k++) {
    int v = compress_k(s, k);
    if (v < res) res = v;
  }
  return res;
}

int main(void)
{
  cout << solution("a") << '\n';
}
