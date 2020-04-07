#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long lld;

int n;
lld a[500000];
int cnt[8010];

int freqs[8000];
int freqs_idx;

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
	sort(a, a+n);
	lld sum = 0;
	int freq = -1;
	for (int i = 0; i < n; i++) sum += a[i];
	for (int i = 0; i < n; i++) cnt[a[i]+4000]++;
	for (int i = 0; i < 8010; i++) {
		if (cnt[i] > freq) {
			freqs[0] = i - 4000;
			freqs_idx = 1;
			freq = cnt[i];
		} else if (cnt[i] == freq) {
			freqs[freqs_idx++] = i - 4000;
		}
	}
	lld avg = (sum + (n/2)) / n;
	if (sum < 0) avg = -((-sum + (n/2))/n);
	sort(freqs, freqs + freqs_idx);
	printf("%lld\n", avg);
	printf("%lld\n", a[n/2]);
	printf("%d\n", freqs_idx > 1 ? freqs[1] : freqs[0]);
	printf("%lld\n", a[n-1]-a[0]);
}
