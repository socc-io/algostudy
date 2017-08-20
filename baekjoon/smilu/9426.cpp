#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int N, K, med_idx, tmp, del;
multiset<int> s;
queue<int> q;
long long sum;

int main(void)
{
	scanf("%d%d", &N, &K);
	med_idx = (K - 1) / 2;
	for(int i = 0; i < K - 1; ++i) {
		scanf("%d", &tmp);
		s.insert(tmp);
		q.push(tmp);
	}
	for(int i = 0; i < N - K + 1; ++i) {
		scanf("%d", &tmp);
		s.insert(tmp);
		q.push(tmp);

		auto it = s.begin();
		advance(it, med_idx);
		sum += *it;

		del = q.front(); q.pop();
		it = s.find(del);
		if(it != s.end()) s.erase(it);
	}
	printf("%lld", sum);
}