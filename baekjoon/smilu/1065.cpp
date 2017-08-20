#include <cstdio>

int N, cnt;
int nums[5];

int main(void)
{
	scanf("%d", &N);
	for(int i=1; i<=N; ++i) {
		for(int j=0;;++j) {
			nums[j]++;
			if(nums[j] == 10) {
				nums[j] = 0;
			} else break;
		}
		bool succ = true;
		for(int j=2, p=100; p <= i; ++j, p *= 10) {
			if(nums[j] - nums[j-1] != nums[1] - nums[0]) {
				succ = false;
				break;
			}
		}
		if(succ) ++cnt;
	}
	printf("%d", cnt);
}