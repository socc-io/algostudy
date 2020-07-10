#include <stdio.h>

int ret[50];
char buf[51];
int par[50];

int root(int v) { return par[v] == v ? v : (par[v] = root(par[v])); }

int main() {  
  int n, m; scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) par[i] = i;
  int alpha = m-n+1;
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    for (int j = i+1; j < n; j++) {
      if (buf[j] == 'N') continue;
      if (root(i) == root(j)) {
        if (alpha > 0) {
          --alpha;
          ret[i]++;
          ret[j]++;
        }
      } else {
        par[root(i)] = root(j);
        ret[i]++;
        ret[j]++;
      }
    }
  }
  int sum = 0; for (int i = 0; i < n; i++) sum += ret[i];
  if (sum != (m<<1)) puts("-1");
  else for (int i = 0; i < n; i++) printf("%d ", ret[i]);
}
