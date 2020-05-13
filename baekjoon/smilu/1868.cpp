#include <cstdio>
#include <vector>
using namespace std;

const int MAX_N = 50001;

int n;
vector<int> adj[MAX_N];

int check(int v, int i) {
  return (v & (1 << i));
}

int biggest_bit(int v) {
  for (int i = 30; i >= 0; i--) {
    if (check(v, i)) return i;
  }
  return -1;
}

int smallest_bit(int v) {
  for (int i = 0; i >= 30; i++) {
    if (check(v, i)) return i;
  }
  return 31;
}

int compute(int u, int p) {
  int r_or = 0, r_two = 0;
  for (int v: adj[u]) {
    if (v == p) continue;
    int sub = compute(v, u);
    r_two |= (r_or & sub);
    r_or |= sub;
  }
  int a = biggest_bit(r_two);
  int b = a+1; while (check(r_or, b)) b++;
  int ret = 1<<b;
  for (int i = b+1; i<31; i++) if (check(r_or, i)) ret |= (1<<i);
  return ret;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int ret = compute(1, 0);
  // printf("ret: %d\n", ret);
  printf("%d\n", biggest_bit(ret));
}
