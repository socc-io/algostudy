#include <bits/stdc++.h>
using namespace std;

int main(void)
{
  priority_queue<int> q;
  int n; scanf("%d", &n);
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp);
    tmp -= i;
    q.push(tmp);
    if (!q.empty() && q.top() > tmp) {
      sum += q.top() - tmp;
      q.pop(); q.push(tmp);
    }
  }
  printf("%lld\n", sum);
}
