#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
using namespace std;

int points[1000001];
int N, K;
int max_point = -1;

void findAB(int *A_c, int *B_c)
{
	int left_cur=0, right_cur=0;
	int left_dup=0, right_dup=0;
	int subtotal = 0;
	*A_c = 0;
	*B_c = 0;
	while(left_cur <= max_point && right_cur <= max_point) {
		if (subtotal < K) {
			right_dup += points[right_cur++];
			subtotal += right_dup;
		}
		else if (subtotal > K) {
			left_dup += points[left_cur++];
			subtotal -= left_dup;
		}
		else {
			*A_c = left_cur;
			*B_c = right_cur;
			return;
		}
		// printf("L: %d, R: %d, T: %d\n", left_cur, right_cur, subtotal);
	}
}

int main(void)
{
	scanf("%d%d", &N, &K);
	for(int i=0;i<1000001;++i) points[i] = 0;
	for(int i=0;i<N;++i) {
		int left, right;
		scanf("%d%d", &left, &right);
		points[left] += 1;
		points[right] -= 1;
		if(max_point < right) max_point = right;
	}
	int a, b;
	findAB(&a, &b);
	printf("%d %d\n", a, b);
}