#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char n[25];
int K, len;

int bitmask(const char* s = n, int end = len) {
  int ans = 0;
  for (int i = 0; i < end; i++) {
    if (s[i] < '0' || '9' < s[i]) continue;
    ans |= (1 << (s[i] - '0'));
  }
  return ans;
}
int cnt_bm(int bm) {
  int ans = 0;
  for (int i = 0; i < 10; i++) {
    if (bm & (1 << i)) ++ans;
  }
  return ans;
}
int cnt(const char* s = n, int end = len) {
  return cnt_bm(bitmask(s, end));
}
int minimum_bm(int bm) {
  for (int i = 0; i < 10; i++) {
    if (bm & (1 << i)) return i;
  }
  return 10;
}
int minimum_nbm(int bm) {
  for (int i = 0; i < 10; i++) {
    if (!(bm & (1 << i))) return i;
  }
  return 10;
}

int main(void)
{
  scanf("%s%d", n, &K);
  len = strlen(n);

  if (cnt() == K) {
    puts(n);
    return 0;
  }
  int p = -1;
  for (int i = len - 1; i >= 0; i--) {
    char cur = n[i] + 1;
    int capa = len - 1 - i;
    while (cur <= '9') {
      n[i] = cur;
      int c = cnt(n, i+1);
      if (c <= K  && K <= c + capa) {
        p = i+1;
        break;
      }
      ++cur;
    }
    if (p != -1) break;
  }
  if (p == -1) {
    len = len + 1 > K ? len + 1 : K;
    n[0] = '1';
    p = 1;
  }

  int kbm = bitmask(n, p);
  int nc = cnt(n, p);

  if (nc < K) {
    int cs[25];
    for (int i = 0; i <= K - nc; i++) {
      cs[i] = minimum_nbm(kbm) + '0';
      kbm |= (1 << (cs[i] - '0'));
    }
    for (int i = p; i < len-(K-nc-1); i++) {
      n[i] = cs[0];
    }
    for (int i = len-(K-nc-1); i < len; i++) {
      n[i] = cs[i-len+K-nc];
    }
  } else {
    char rep = minimum_bm(kbm) + '0';
    for (int i = p; i < len; i++) {
      n[i] = rep;
    }
  }
  
  puts(n);
}