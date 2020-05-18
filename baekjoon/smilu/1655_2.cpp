#include <bits/stdc++.h>
using namespace std;

priority_queue<int> pl;
priority_queue<int,vector<int>,greater<int>> pr;

int main(void)
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int val; scanf("%d", &val);
    if (pl.empty() || pl.top() >= val) pl.push(val);
    else pr.push(val);
    if (pl.size() >= pr.size() + 2) {
      pr.push(pl.top());
      pl.pop();
    } else if (pr.size() > pl.size()) {
      pl.push(pr.top());
      pr.pop();
    }
    printf("%d\n", pl.top());
  }
}
