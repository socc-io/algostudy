#include <cstdio>

int main(void)
{
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    int temp;
    scanf("%d", &temp);
    sum += temp * temp;
  }
  printf("%d", sum % 10);
  return 0;
}