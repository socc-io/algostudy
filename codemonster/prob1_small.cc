#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long ans, chk;
int a[10];
int b[10];
bool v[10];
int d[10];

void dfs(int depth)
{
	if(depth == n) {
        long long val = 0;
		for(int i=0; i<n; ++i) {
			val = val * a[d[i]] + b[d[i]];
		}
		long long s_chk = 0;
		for(int i=0; i<n; ++i) {
			s_chk += (i+1) * (d[i]+1);
		}
		if((ans < val) || (ans == val && s_chk < chk)) {
			ans = val;
			chk = s_chk;
		}
        return;
	}
	for(int i=0; i<n; ++i) {
		if(v[i]) continue;
		v[i] = true;
		d[depth] = i;
		dfs(depth + 1);
		v[i] = false;
	}
}

void do_task()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		scanf("%d%d", a+i, b+i);
        v[i] = false;
	}
	ans = -1000000000;
    chk = -1000000000;
	dfs(0);
    printf("%lld\n", chk);
}

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t--) do_task();
	return 0;
}
