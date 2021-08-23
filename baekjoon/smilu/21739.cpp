#include <cstdio>

typedef long long ll;

const ll mod = 1000000007;
ll m[10010][10010];

int inv(int x) {
	int r, b = mod-2;
	for (r = 1; b; b >>= 1) {
		if ((b & 1)) r = (1ll * r * x) % mod;
		x = (1ll * x * x) % mod;
	}
	return r;
}

int main() {
	int n;
	scanf("%d", &n);
	int u = 1, d = 1;
	for (int i = n+1; i <= (n<<1); i++)
		u = (1ll * u * i) % mod;
	for (int i = 1; i <= n+1; i++)
		d = (1ll * d * i) % mod;
	printf("%lld", (1ll * u * inv(d)) % mod);
}
