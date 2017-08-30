#include <cstdio>
#include <set>
#include <algorithm>

int N, tmp, arr[500000], sum, cnt[8001], min = 4001, max = -4001, c;

int main(void)
{
	std::set<int> S;

	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", &tmp);
		arr[i] = tmp;
		sum += tmp;
		if(tmp < min) min = tmp;
		if(tmp > max) max = tmp;
		cnt[tmp + 4000]++;
	}
	std::sort(arr, arr+N);

	for(int i = 1; i <= 8000; ++i) {
		if(c < cnt[i]) {
			c = cnt[i];
			S.clear();
			S.insert(i - 4000);
		} else if(c == cnt[i]) {
			S.insert(i - 4000);
		}
	}

	auto it = S.begin();
	if(S.size() > 1 ) ++it;

	printf("%.0f\n%d\n%d\n%d", ((double)sum) / N, arr[N/2], *it, max - min);
}