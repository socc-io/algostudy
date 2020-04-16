#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main(void)
{
  int n;
  scanf("%d", &n);
  vector<int> v(n), u(n);
  for (int i = 0; i < n; i++) scanf("%d", &v[i]);
  for (int i = 0; i < n; i++) u[i] = v[i];
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  map<int, int> rank;
  for (int i = 0; i < v.size(); i++) rank[v[i]] = i;
  for (int i = 0; i < n; i++) printf("%d ", rank[u[i]]);
  puts("");
}
