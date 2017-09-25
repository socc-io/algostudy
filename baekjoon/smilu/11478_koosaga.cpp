#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long lint;
const int mod = 10007;

int n;
char str[1005];
int ord[1005], nord[1005], sfx[1005], rev[1005], p = 1;

bool cmp(int a, int b){
	if(ord[a] != ord[b]) return ord[a] < ord[b];
	return ord[a + p] < ord[b + p];
}

int main(){
	scanf("%s",str);
	n = strlen(str);
	for(int i=0; i<n; i++){
		ord[i] = str[i];
		sfx[i] = i;
	}
	ord[n] = -1;
	while(1){
		sort(sfx, sfx + n, cmp);
		if(p * 2 >= n) break;
		for(int i=1; i<n; i++){
			nord[sfx[i]] = nord[sfx[i-1]];
			if(cmp(sfx[i-1], sfx[i])) nord[sfx[i]]++;
		}
		memcpy(ord, nord, n * sizeof(int));
		p <<= 1;
	}
	for(int i=0; i<n; i++){
		rev[sfx[i]] = i;
	}
	lint ret = 0;
	int h = 0;
	for(int i=0; i<n; i++){
		if(rev[i]){
			int j = sfx[rev[i] - 1];
			while(str[i + h] == str[j+h]) h++;
			ret += h;
		}
		h = max(h-1, 0);
	}
	printf("%lld",1ll * n * (n+1) / 2 - ret);
}
