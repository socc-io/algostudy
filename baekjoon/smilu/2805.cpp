#include <cstdio>
#include <cstdlib>
#include <algorithm>

long long N, L;
long long tree_length[1000001];

int main(void)
{
	scanf("%d%d", &N, &L);
	for(int i=0; i<N; ++i) {
		scanf("%d", tree_length + i);
	}

	std::sort(tree_length, tree_length + N, [](long long a, long long b) {
		return a > b;
	});

	tree_length[N++] = 0;

	long long cut_length = 0;
	long long tree_idx = 1;
	for(; tree_idx<N; ++tree_idx) {
		long long length_offset = tree_length[tree_idx - 1] - tree_length[tree_idx];
		cut_length += tree_idx * length_offset;
		if (cut_length >= L) break;
	}

	long long cut_height = tree_length[tree_idx];

	long long over_length = cut_length - L;

	cut_height += over_length / tree_idx;

	printf("%lld", cut_height);

	return 0;
}