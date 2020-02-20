#include <cstdio>
#include <set>
using namespace std;

void solve() {
  int n;
  multiset<int> s;
  scanf("%d", &n);
  while(n--) {
    char ops[2];
    int value;
    scanf("%s%d", ops, &value);
    if (ops[0] == 'I') {
      s.insert(value);
    } else if (!s.empty()) {
      if (value == 1) {
        auto it = s.end();
        --it;
        s.erase(it);
      } else {
        s.erase(s.begin());
      }
    }
  }
  if (s.empty()) puts("EMPTY");
  else {
    auto e = s.end();
    --e;
    printf("%d %d\n", *e, *s.begin());
  }
}

int main(void)
{
  int t;
  scanf("%d", &t);
  while(t--) solve();
}