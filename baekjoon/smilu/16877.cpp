#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MAX_FIBO 35

int fibo[MAX_FIBO];
void init_fibo() {
  fibo[0] = 1;
  fibo[1] = 2;
  for (int i = 2; i < MAX_FIBO; i++) {
    fibo[i] = fibo[i-2] + fibo[i-1];
  }
}

int g[3000001];
bool c[30];

void init_g() {
  g[0] = 0;
  g[1] = 1;
  for (int i = 2; i < 3000001; i++) {
    for (int fi = 0; fi < MAX_FIBO; fi++) {
      int v = i - fibo[fi];
      if (v < 0) break;
      c[g[v]] = true;
    }
    while (c[g[i]]) ++g[i];
    memset(c, 0x00, sizeof(c));
  }
}

int main(void)
{
  init_fibo();
  init_g();

  int n;
  int ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int t; scanf("%d", &t);
    ans ^= g[t];
  }

  puts(ans > 0 ? "koosaga" : "cubelover");
}
