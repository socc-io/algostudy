#include <cstdio>
#include <cstring>

bool s[21];

int main(void)
{
  int n;
  scanf("%d", &n);
  while(n--) {
    char cmd[7]; int val = 0;
    scanf("%s", cmd);
    if (strcmp(cmd, "add") == 0) {
      scanf("%d", &val);
      s[val] = 1;
    } else if (strcmp(cmd, "remove") == 0) {
      scanf("%d", &val);
      s[val] = 0;
    } else if (strcmp(cmd, "check") == 0) {
      scanf("%d", &val);
      printf("%d\n", s[val] ? 1 : 0);
    } else if (strcmp(cmd, "toggle") == 0) {
      scanf("%d", &val);
      s[val] = !s[val];
    } else if (strcmp(cmd, "all") == 0) {
      for (int i = 1; i <= 20; i++) s[i] = 1;
    } else if (strcmp(cmd, "empty") == 0) {
      for (int i = 1; i <= 20; i++) s[i] = 0;
    }
  }
}