#include <iostream>

int ans;

long long pow(int a, int b)
{
	long long res = 1;
	int m = a;
	while(b) {
		if(b & 1) {
			res *= m;
		}
		m *= m;
		b >>= 1;
	}
	return res;
}

void find(int pos, int p_num)
{
	if(pos == 1) {
		if(p_num == 0) {
			ans++;
		}
		return;
	}
	long long left = pow(3, p_num / 2);

	for(int i = pos; i >= left; --i) {
		if(i % 3 == 0 && p_num >= 2) {
			find(i / 3, p_num - 2);
		}

		p_num++;
		left = pow(3, p_num / 2);
	}
}

int solution(int n) {
    ans = 0;

    find(n, 0);

    return ans;
}

int main(void)
{
	printf("%d\n", solution(2147483647));
}