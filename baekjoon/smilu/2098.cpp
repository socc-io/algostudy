#include<iostream>
#include<queue>
#include<map>
using namespace std;

#define MASK 65535  // (1 << 16) - 1

int n;
int w[16][16];

int main()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) scanf("%d", w[i] + j);
	queue<int> Q;  // queue
	map<int, int> mc;  // min cost
	Q.push(1);
	mc[1] = 0;
	int ans = 1234567890;
	int allv = (1 << n) - 1;
	while(!Q.empty()) {
		int s = Q.front(); Q.pop();
		int pos = s >> 16;
		int visit = s & MASK;
		if(visit == allv) {
			if(w[pos][0] == 0) continue;
			int nc = mc[s] + w[pos][0];
			if(nc < ans) ans = nc;
			continue;
		}
		for(int i=0; i<n; ++i) {
			if(w[pos][i] == 0) continue;
			if(visit & (1 << i)) continue;
			int ns = (i << 16) | (visit | (1 << i));
			int nc = mc[s] + w[pos][i];
			if(mc.find(ns) == mc.end()) {
				mc[ns] = nc;
				Q.push(ns);
			} else if(mc[ns] > nc) {
				mc[ns] = nc;
			}
		}
	}
	printf("%d", ans);
}