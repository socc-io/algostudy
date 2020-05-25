#include <bits/stdc++.h>
using namespace std;

int n, d;
pair<int,int> rgs[100000];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &rgs[i].first, &rgs[i].second);
    if (rgs[i].first < rgs[i].second) swap(rgs[i].first, rgs[i].second);
  }
  scanf("%d", &d);
  sort(rgs, rgs+n);
  for (int i = 0; i < n; i++) {
    swap(rgs[i].first, rgs[i].second);
  }
  priority_queue<int, vector<int>, greater<int>> q;
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int th = rgs[i].second - d;
    q.push(rgs[i].first);
    while (!q.empty() && q.top() < th) q.pop();
    ans = max(ans, (int)q.size());
  }
  printf("%u\n", ans);
}
