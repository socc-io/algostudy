#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 1505

typedef long long ll;

struct BIT {
  ll ft[MAX_N];
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  void update(int a, int b, ll v) {
    update(a, v);
    update(b+1, -v);
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
} bit[MAX_N];

int n;
ll c[MAX_N][MAX_N];
ll d[MAX_N][MAX_N];
ll sum;

ll g(int x, int y) { // get
  return d[x][y] + bit[x].query(y);
}

bool right(int x, int y, int v) {
  if (y >= n) return false;
  return max(g(x-1, y+1), g(x, y)) + v == max(g(x-1, y+1), g(x, y) + v);
}

bool down(int x, int y, int v) {
  if (x >= n) return false;
  return max(g(x+1, y-1), g(x, y)) + v == max(g(x+1, y-1), g(x, y) + v);
}

int s[MAX_N], e[MAX_N];
ll query(int x, int y, int v){
	s[x] = e[x] = y;
	for(int i=x+1; i<=n; i++) s[i] = n+1, e[i] = 0;

	for(int i=x, j=y;;){
		if(right(i,j,v)) j++;
		else i++;
		if(i > n) break;
		e[i] = j;
	}
	for(int i=x, j=y;;){
		if(down(i,j,v)) i++;
		else j++;
		if(j > n || e[i] < j) break;
		s[i] = min(s[i], j);
	}

	for(int i=x; i<=n; i++){
		if(s[i] > e[i]) continue;
		bit[i].update(s[i], e[i], v);
		sum += v * (e[i] - s[i] + 1);
	}
	return sum;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%lld", &c[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      d[i][j] = max(d[i-1][j], d[i][j-1]) + c[i][j];
      sum += d[i][j];
    }
  }
  printf("%lld\n", sum);
  for (int i = 0; i < n; i++) {
    char cmd[2]; int a, b;
    scanf("%s%d%d", cmd, &a, &b);
    if (cmd[0] == 'U') {
      printf("%lld\n", query(a, b, 1)); 
    } else { // 'D'
      printf("%lld\n", query(a, b, -1)); 
    }
  }
}
