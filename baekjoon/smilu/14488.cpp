#include <cstdio>
#include <cstdlib>

long long n;
double T;
long long pos[50000];
long long v[50000];

#define INF (0x7FFFFFFF)
#define MINF (0x80000000)

double left, right;

template <class T>
inline T max(T a, T b) {
	return a > b ? a : b;
}
template <class T>
inline T min(T a, T b) {
	return a < b ? a : b;
}

int answer()
{
	double dist;
	left = 0; right = 1000000001;
	for(long long i=1; i<n; ++i) {
		dist = v[i] * T;
		left = max(left, pos[i] - dist);
		right = min(right, pos[i] + dist);
		if(left > right) return 0;
	}
	return 1;
}

int main(void)
{
	scanf("%lld%lf", &n, &T);
	for(long long i=0; i<n; ++i) {
		scanf("%lld", pos+i);
	}
	for(long long i=0; i<n; ++i) {
		scanf("%lld", v+i);
	}
	printf("%d", answer());
	return 0;
}