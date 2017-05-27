#include <cstdio>
#include <cstdlib>

#define INF 0xFFFFFF

int N;
int box[1001];
int lis[1001];

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d", box+i);
	}
	lis[0] = 1;
	int max_lis = 1;
	for(int i=1; i<N; ++i) {
		lis[i] = 1;
		for(int j=0; j<i; ++j) {
			if(box[j] < box[i] && lis[j]+1 > lis[i]) {
				lis[i] = lis[j]+1;
			}
		}
		if(max_lis < lis[i]) max_lis = lis[i];
	}
	printf("%d", max_lis);
}