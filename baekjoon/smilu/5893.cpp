#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1010];
char v[1010];

int main(void)
{
  scanf("%s", s);
  int n = strlen(s), i, k;
  for (i = 0; i < n; i++) v[i] = s[n-1-i] - '0';
  for (i = 0; i < n; i++) v[i+4] += s[n-1-i] - '0';
  for (i = 0; i < 1009; i++) {
    if (v[i] == 2) v[i] = 0, v[i+1] += 1;
    if (v[i] == 3) v[i] = 1, v[i+1] += 1;
  }
  for (k = 1009; k >= 0; k--) if (v[k]) break;
  for (i = k; i >= 0; i--) putchar('0'+v[i]);
}