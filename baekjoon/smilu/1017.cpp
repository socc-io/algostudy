#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_PRIME 2001
#define MAX_N 100

#define L_INF 0xFFFFFFFFFFFFFFFF

int N;
int arr[MAX_N];

bool is_prime[MAX_PRIME];

int match[MAX_N];
unsigned long long lock;

std::vector<int> conn[MAX_N];

int ans[MAX_N];
int ans_num;

bool try_match(int w)
{
	lock |= (1 << w);

	for(auto vit = conn[w].begin(); vit != conn[w].end(); ++vit) {
		int v = *vit;

		if(lock & (1<< v))
			continue;

		lock |= (1 << v);

		if(match[v] == -1 || try_match(match[v])) {
			match[w] = v;
			match[v] = w;

			// printf("(%d, %d) ", arr[w], arr[v]);

			lock &= L_INF - (1 << w) - (1 << v);

			return true;
		}

		lock &= L_INF - (1 << v);
	}

	lock &= L_INF - (1 << w);

	return false;
}

int main(void)
{
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", arr + i);
	}

	for(int i = 2; i < MAX_PRIME; ++i)
		is_prime[i] = true;

	is_prime[0] = false;
	is_prime[1] = false;

	for(int i = 2; i < MAX_PRIME; ++i) {
		if(false == is_prime[i])
			continue;
		for(int j = (i << 1); j < MAX_PRIME; j += i) {
			is_prime[j] = false;
		}
	}

	for(int i = 1; i < N; ++i) {
		for(int j = i + 1; j < N; ++j) {
			if(is_prime[arr[i] + arr[j]]) {
				conn[i].push_back(j);
				conn[j].push_back(i);
			}
		}
	}

	lock = 1;

	for(int i = 0; i < N; ++i) match[i] = -1;

	ans_num = 0;
	for(int i = 1; i < N; ++i) {

		if(false == is_prime[arr[0] + arr[i]])
		  continue;

		if(match[i] != -1) {
			match[match[i]] = -1;
			match[i] = -1;
		}

		match[0] = i;
		match[i] = 0;
		lock |= (1 << i);

		bool success = true;
		for(int j = 1; j < N; ++j) {
			if(match[j] == -1 && false == try_match(j)) {
				success = false;
				break;
			}
		}

		match[i] = -1;	
		lock &= L_INF - (1 << i);

		if(success) {
			ans[ans_num++] = arr[i];
		}
	}

	if(ans_num == 0) {
		puts("-1");
	} else {
		std::sort(ans, ans + ans_num);
		for(int i = 0; i < ans_num; ++i) {
			printf("%d ", ans[i]);
		}
	}

	return 0;
}