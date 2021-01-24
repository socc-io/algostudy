#include <bits/stdc++.h>
using namespace std;

int w, n;
int wei[5050];
bool chk[800000];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> w >> n;
  for (int i = 0; i < n; i++) cin >> wei[i];

  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      const int s = w - wei[i] - wei[j];
      if (s >= 0 && chk[s]) {
        puts("YES");
        return 0;
      }
    }
    for (int j = 0; j < i; j++) {
      const int s = wei[i] + wei[j];
      if (s < w) {
        chk[s] = true;
      }
    }
  }
  puts("NO");
}
