#include<cstdio>
#include<algorithm>

#define MAXN (1<<21)

int w[MAXN], k, maxn, tmp;
long long ans;

inline void get(int &v) {
	register int ch;
	v = getchar_unlocked() & 15;
	while((ch = getchar_unlocked()) > 40) v = v*10 + (ch & 15);
}

int main()
{
	get(k);
	maxn = (2 << k);
	for(int i=2; i<maxn; ++i) get(w[i]);
	for(int i=(maxn>>1); --i;) {
		w[i] += tmp = std::max(w[i << 1], w[(i << 1) | 1]);
		ans += tmp;
	}
	printf("%lld", ans + w[1]);
}