#include <cstdio>

int N;
int nums_tmp[10];
int nums_num;
int *nums;
int ans[10];
int log_n;

int pow(int a, int b)
{
	if(b < 0) return 0;
	int res = 1;
	while(b) {
		if(b & 1) {
			res *= a;
		}
		a *= a;
		b >>= 1;
	}
	return res;
}

int main(void)
{
	int tmp;

	scanf("%d", &N);
	tmp = N;
	nums_num = 9;
	while(tmp) {
		nums_tmp[nums_num--] = tmp % 10;
		tmp /= 10;
	}
	nums = nums_tmp + (nums_num + 1);
	nums_num = 9 - nums_num;
	log_n = nums_num - 1;

	for(int i = 0; i < 10; ++i) ans[i] = 0;

	int left = 0;
	int right = N - pow(10, log_n) * nums[0];

	for(int i = 0; i < nums_num; ++i) {

		for(int j = 0; j < 10; ++j) {
			if(j < nums[i]) {
				ans[j] += (left + (j != 0)) * pow(10, log_n - i);
			} else if(j == nums[i]) {
				ans[j] += (left - 1 + (j != 0)) * pow(10, log_n - i) + right + 1;
			} else {
				ans[j] += left * pow(10, log_n - i);
			}
		}

		left = left * 10 + nums[i];
		right -= pow(10, log_n - 1 - i) * nums[1 + i];
	}

	for(int i = 0; i < 10; ++i) {
		printf("%d ", ans[i]);
	}

	return 0;
}