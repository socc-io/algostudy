#include <cstdio>

int N, N2, tmp, cnt;
int arr[200000];
bool in_basket[100000];

int main(void)
{
	scanf("%d", &N);
	N2 = N << 1;
	cnt = 0;
	int max_cnt = 0;
	for(int i=0; i<N2; ++i) {
		scanf("%d", &tmp);
		tmp--;
		in_basket[tmp] = !in_basket[tmp];
		if(in_basket[tmp]) {
			cnt++;
		} else{
			cnt--;
		}
		if(max_cnt < cnt) {
			max_cnt = cnt;
		}
	}
	printf("%d", max_cnt);
}