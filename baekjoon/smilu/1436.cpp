/*
 * Solving https://www.acmicpc.net/problem/1436
 */

#include <cstdio>

int max2(int a, int b) {
  if (a < b) return b;
  return a;
}

int count_digit_sequence_from_number(int num, int digit, int base = 10)
{
  int ans = 0;
  int cnt = 0;
  while (num > 0) {
    int last_digit = num % base;
    if (last_digit == digit) {
      cnt++;
      ans = max2(ans, cnt);
    } else {
      cnt = 0;
    }
    num /= base;
  }
  return ans;
}

bool is_endnumber(int num)
{
  int num_six = count_digit_sequence_from_number(num, 6);
  if (num_six >= 3) return true;
  return false;
}

int nth_endnumber(int n)
{
  int nth = 0;
  for (int i = 1; i < 100000000; i++) {
    if (is_endnumber(i)) {
      nth++;
      if (nth == n) {
        return i;
      }
    }
  }
  return -1;
}

int main(void)
{
  int n;
  scanf("%d", &n);
  printf("%d", nth_endnumber(n));
}
