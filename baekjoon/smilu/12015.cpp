#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1000000];

vector<int> lis;

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
  lis.push_back(arr[0]);
  for (int i = 1; i < n; i++) {
    if (lis.back() < arr[i]) lis.push_back(arr[i]);
    else {
      *lower_bound(lis.begin(), lis.end(), arr[i]) = arr[i];
    }
  }
  printf("%lu\n", lis.size());
}
