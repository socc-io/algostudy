#include <cstdio>
#include <cstring>

bool is_palindrome(const char* s) {
  int len = strlen(s);
  int half = len / 2;
  for (int i = 0; i < half; i++) {
    if (s[i] != s[len-1-i]) return false;
  }
  return true;
}

int main(void)
{
  char s[6];
  while(1) {
    scanf("%s", s);
    if (s[0] == '0' && s[1] == 0) break;
    puts(is_palindrome(s) ? "yes" : "no");
  }
}