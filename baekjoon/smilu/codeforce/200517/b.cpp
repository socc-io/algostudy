#include <bits/stdc++.h>
using namespace std;

char str[200001];
int len;

vector<int> pos[4];

int find_position(int val, int offset)
{
  auto it = upper_bound(pos[val].begin(), pos[val].end(), offset);
  if (it == pos[val].end()) return -1;
  return *it;
}

void solve()
{
  scanf("%s", str);
  len = strlen(str);
  for (int i = 0; i < 4; i++) pos[i].clear();
  for (int i = 0; i < len; i++) {
    char ch = str[i];
    int val = ch - '0'; 
    pos[val].push_back(i);
  }
  int ans = 0x3f3f3f3f;
  for (int i = 0; i < len; i++) {
    int found[4] = {-1, -1, -1, -1};
    char ch = str[i];
    int val = ch - '0';
    found[val] = i;
    bool flag = false;
    for (int j = 1; j <= 3; j++) {
      if (found[j] != -1) continue;
      found[j] = find_position(j, i);
      if (found[j] == -1) {
        flag = true;
        break;
      }
    }
    if (flag) continue;
    // printf("pos: %d, (%d, %d, %d)\n", val, found[1], found[2], found[3]);
    int most_right = max(found[1], max(found[2], found[3]));
    int sub = most_right - i + 1;
    ans = min(ans, sub);
  }
  printf("%d\n", ans == 0x3f3f3f3f ? 0 : ans);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
