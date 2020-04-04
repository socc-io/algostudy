#include <cstdio>
#include <vector>
using namespace std;

int n, m;
int a[500000];
int lazy[2000000];

inline bool coprime(int a, int b, int c, int d) {
  return d <= a || b <= c;
}

inline bool including(int a, int b, int c, int d) {
  return a <= c && d <= b;
}

void update_lazy(int t_index, int t_begin, int t_end, int begin, int end, int value) {
  if (coprime(begin, end, t_begin, t_end)) return;
  if (including(begin, end, t_begin, t_end)) {
    lazy[t_index] ^= value;
    return;
  }
  int t_mid = (t_begin + t_end) >> 1;
  int t_left = t_index << 1;
  int t_right = t_left + 1;
  update_lazy(t_left , t_begin, t_mid, begin, end, value);
  update_lazy(t_right, t_mid  , t_end, begin, end, value);
}

void apply_lazy(int t_index, int t_begin, int t_end, int index) {
  if (index < t_begin || t_end <= index) return;
  if (t_begin + 1 == t_end) {
    a[t_begin] ^= lazy[t_index];
    lazy[t_index] = 0;
    return;
  }
  int t_mid = (t_begin + t_end) >> 1;
  int t_left = t_index << 1;
  int t_right = t_left + 1;
  lazy[t_left ] ^= lazy[t_index];
  lazy[t_right] ^= lazy[t_index]; 
  lazy[t_index] = 0;
  apply_lazy(t_left , t_begin, t_mid, index);
  apply_lazy(t_right, t_mid  , t_end, index);
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int cmd; scanf("%d", &cmd);
    if (cmd == 1) {
      int begin, end, value;
      scanf("%d%d%d", &begin, &end, &value);
      update_lazy(1, 0, n, begin, end + 1, value);
    } else {
      int index;
      scanf("%d", &index);
      apply_lazy(1, 0, n, index);
      // for (int i = 0; i < 16; i++) printf("%d ", lazy[i]); puts("")
      printf("%d\n", a[index]);
    }
  }
}