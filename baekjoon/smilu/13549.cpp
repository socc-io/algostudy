#include <cstdio>
#include <queue>
using namespace std;

int min_cost[100001];

#define INF (0x7FFFFFFF)

// 10001
// 00101

int main(void)
{
	for(int i=0; i<100001; ++i) {
		min_cost[i] = INF;
	}

	int src, dest;
	scanf("%d%d", &src, &dest);

  if (src > dest) {
    printf("%d", src - dest);
    return 0;
  }

	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
  Q.push(make_pair(0, src));
  min_cost[src] = 0;

	while(!Q.empty()) {
		int f = Q.top().second; Q.pop();
		int c = min_cost[f];

		if(f == dest) {
			printf("%d", c);
			return 0;
		}

    int ks[3] = {f << 1, f + 1, f - 1};
    for (int i = 0; i < 3; i++) {
      int k = ks[i];
      if(k <= 100000 && c < min_cost[k]) {
        int nc = c + (i > 0 ? 1 : 0);
        Q.push(make_pair(nc, k));
        min_cost[k] = nc;
      }
    }
	}
}