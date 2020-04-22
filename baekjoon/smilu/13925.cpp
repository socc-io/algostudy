#include <cstdio>

typedef long long lld;

const lld MAX_V = 404040;
const lld MOD = 1e9+7;

lld v[MAX_V], la[MAX_V], lb[MAX_V]; // la * v + lb;

lld build(int node, int begin, int end) {
  if (begin == end) {
    scanf("%lld", &v[node]);
    return v[node];
  }
  int mid = (begin + end) >> 1;
  return v[node] = (build(node<<1, begin, mid)
    + build((node<<1)+1, mid+1, end)) % MOD;
}

void update_lazy(int node, int begin, int end) {
  if (la[node] == 1 && lb[node] == 0) return;
  lld sz = end - begin + 1;
  int left = node<<1, right = left + 1;
  if (begin < end) {
    la[left ] = (la[node] * la[left ]) % MOD;
    lb[left ] = (la[node] * lb[left ] + lb[node]) % MOD;
    la[right] = (la[node] * la[right]) % MOD;
    lb[right] = (la[node] * lb[right] + lb[node]) % MOD;
  }
  v[node] = (la[node] * v[node] + lb[node] * sz) % MOD;
  la[node] = 1; lb[node] = 0;
}

void update(int node, int begin, int end, int from, int to, lld m, lld a) {
  update_lazy(node, begin, end);
  if (to < begin || end < from) return;
  if (from <= begin && end <= to) {
    la[node] *= m; la[node] %= MOD;
    lb[node] *= m; lb[node] %= MOD;
    lb[node] += a; lb[node] %= MOD;
    update_lazy(node, begin, end);
    return;
  }
  int mid = (begin + end) >> 1;
  update(node<<1, begin, mid, from, to, m, a);
  update((node<<1)+1, mid+1, end, from, to, m, a);
  v[node] = (v[node<<1] + v[(node<<1)+1]) % MOD;
}

lld query(int node, int begin, int end, int from, int to) {
  update_lazy(node, begin, end);
  if (to < begin || end < from) return 0;
  if (from <= begin && end <= to) return v[node] % MOD;
  int mid = (begin + end) >> 1;
  return (query(node<<1, begin, mid, from, to) +
         query((node<<1)+1, mid+1, end, from, to)) % MOD;
}

int main(void)
{
  int n, m;
  scanf("%d", &n);
  build(1, 1, n);
  for (int i = 0; i < MAX_V; i++) la[i] = 1, lb[i] = 0;
  scanf("%d", &m);
  while (m--) {
    int cmd, x, y, v;
    scanf("%d%d%d", &cmd, &x, &y);
    if (cmd != 4) scanf("%d", &v);
    if (cmd == 1) {
      update(1, 1, n, x, y, 1, v);
    } else if (cmd == 2) {
      update(1, 1, n, x, y, v, 0);
    } else if (cmd == 3) {
      update(1, 1, n, x, y, 0, v);
    } else {
      printf("%lld\n", query(1, 1, n, x, y));
    }
    // print_status();
  }
}
