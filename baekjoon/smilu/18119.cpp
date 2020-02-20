#include <cstdio>
#include <vector>
using namespace std;

vector<int> ics[26];
int rem[10000][26];
int wcnt[10000];
char buf[1001];

int main(void)
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    vector<bool> vs(26, false);
    for (char* ch = buf; *ch != 0; ch++) {
      char c = *ch;
      int idx = c - 'a';
      if (vs[idx]) continue;
      vs[idx] = true;
      ics[idx].push_back(i);
      rem[i][idx] = 2;
    }
  }
  for (int i = 0; i < m; i++) {
    int o; char xs[2];
    scanf("%d %s", &o, xs);
    char x = xs[0];
    int idx = x - 'a';
    for (int j = 0; j < ics[idx].size(); j++) {
      int wi = ics[idx][j];
      rem[wi][idx] = o;
      wcnt[wi] += o * 2 - 3;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (wcnt[i] == 0) ++cnt;
    }
    printf("%d\n", cnt);
  }
}
