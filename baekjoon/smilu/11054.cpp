#include <cstdio>

int n;
int arr[1000];

int ltr[1000];
int rtl[1000];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (arr[i] > arr[j]) {
        if (ltr[i] < ltr[j] + 1) {
          ltr[i] = ltr[j] + 1;
        }
      }
    }
  }

  for (int i = n-2; i >= 0; i--) {
    for (int j = i+1; j < n; j++) {
      if (arr[i] > arr[j]) {
        if (rtl[i] < rtl[j] + 1) {
          rtl[i] = rtl[j] + 1;
        }
      }
    }
  }

  int max = 0;
  for (int i = 0; i < n; i++) {
    if (max < ltr[i] + rtl[i]) {
      max = ltr[i] + rtl[i];
    }
  }
  printf("%d", max + 1);
}