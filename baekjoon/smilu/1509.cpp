#include <bits/stdc++.h>
using namespace std;

char str[2501];
vector<int> lefts[2500];
int dp[2500];
int n;

int main(void)
{
  scanf("%s", str);
  n = strlen(str);
  for (int m = 0; m < n; m++) {
    for (int len = 1;; len++) {
      int left = m-len, right = m+len;
      if (left < 0 || right >= n) break;
      if (str[left] != str[right]) break;
      lefts[right].push_back(left);
    }
    for (int len = 1;; len++) {
      int left = m-len+1, right = m+len;
      if (left < 0 || right >= n) break;
      if (str[left] != str[right]) break;
      lefts[right].push_back(left);
    }
  }
  for (int i = 0; i < n; i++) {
    int tmp = dp[i-1] + 1;
    for (int l: lefts[i]) {
      if (l == 0) { tmp = 1; break; }
      else tmp = min(tmp, dp[l-1] + 1);
    }
    dp[i] = tmp;
  }
  printf("%d\n", dp[n-1]);
}
