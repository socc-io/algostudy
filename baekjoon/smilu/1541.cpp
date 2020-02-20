#include <cstdio>
#include <cstdlib>

char fs[51];
int ns[51];
char signs[51];
int ns_len = 0;

int main(void)
{
  scanf("%s", fs);

  char sign = '+';
  char* start = fs;
  for (char* ch = fs;; ch++) {
    char c = *ch;
    if (c == '+' || c == '-' || c == 0) {
      *ch = 0;
      int v = atoi(start);
      if (sign == '-') v = -v;
      signs[ns_len] = sign;
      ns[ns_len++] = v;
      sign = c;
      start = ch + 1;
      if (c == 0) break;
    }
  }

  int first_neg = 0;
  for (; first_neg < ns_len; first_neg++)
    if (signs[first_neg] == '-') break;
  
  for (int i = first_neg; i < ns_len; i++)
    if (ns[i] > 0) ns[i] *= -1;

  int sum = 0;
  for (int i = 0; i < ns_len; i++)
    sum += ns[i];
  printf("%d", sum);
}