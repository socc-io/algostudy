#include <cstdio>

int N, Q;

int arr[1000];
int sum[1001];

int main(void)
{
	scanf("%d%d", &N, &Q);

	sum[0] = 0;
	int res, op, tmp;

	for(int i=0; i<N; ++i) {
		scanf("%d", arr + i);
		sum[i+1] = sum[i] + arr[i];
	}

	for(int i=0; i<Q; ++i) {
		scanf("%d", &op);
		int a, b, c, d;
		if(op == 1) {
			scanf("%d%d", &a, &b);
			a--; b--;
			res = sum[b+1] - sum[a];
			printf("%d\n", res);
			d = arr[b] - arr[a];
			for(int j=a; j<b; ++j) {
				sum[j+1] += d;
			}
			tmp = arr[a];
			arr[a] = arr[b];
			arr[b] = tmp;
		} else if(op == 2) {
			scanf("%d%d%d%d", &a, &b, &c, &d);
			res = sum[b] - sum[a-1] + sum[c-1] - sum[d];
			printf("%d\n", res);
		}
	}
}