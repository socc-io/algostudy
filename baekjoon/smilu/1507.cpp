
#include <iostream>
#include <vector>

using namespace std;

#define INF 1000000000

int n;
int mf[20][20];
int nf[20][20];

void floyd()
{
	for(int k=0; k<n; ++k) {
		for(int i=0; i<n; ++i) {
			for(int j=0; j<n; ++j) {
				int nw = nf[i][k] + nf[k][j];
				if(nw < nf[i][j]) {
					nf[i][j] = nw;
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			scanf("%d", mf[i] + j);
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			nf[i][j] = INF;
		}
	}
	for(int i=0; i<n; ++i) {
		nf[i][i] = 0;
	}
	int ans = 0;
	floyd();
	while(1) {
		int nu, nv, nw = INF;
		for(int i=0; i<n; ++i) {
			for(int j=i+1; j<n; ++j) {
				if(mf[i][j] < nf[i][j] && mf[i][j] < nw) {
					nw = mf[i][j];
					nu = i;
					nv = j;
				} else if(mf[i][j] > nf[i][j]) {
					ans = -1;
				}
			}
		}
		if(nw == INF || ans == -1) break;
		nf[nu][nv] = nw;
		nf[nv][nu] = nw;
		ans += nw;
		floyd();
	}
	printf("%d", ans);
}
