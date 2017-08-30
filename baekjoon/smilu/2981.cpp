#include <cstdio>
#include <set>
#include <algorithm>

int N;
int arr[100];
std::set<int> ans;

int gcd(int a, int b)
{
	int tmp;
	if(a == 0) return b;
	if(a < b) {
		b = b % a;
	}
	while(b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

void push_ans(int val, int min)
{
	if(min < 1) min = 1;
	int divider = 1;
	while(val / divider > min) {
		if(val % divider == 0) {
			ans.insert(val / divider);
		}
		++divider;
	}
}

int main(void)
{
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) scanf("%d", arr + i);
	std::sort(arr, arr+N);
	int m = arr[0];
	for (int d = 0; arr[0]; ++d) {
		int g = arr[0];
		for(int i = 1; i < N && d < g; ++i) {
			g = gcd(g, arr[i]);
		}
		if(g > 1 && d < g) {
			push_ans(g, d);
		}
		for(int i = 0; i < N; ++i) --arr[i];
	}
 	int g = arr[1];
 	for(int i = 2; i < N; ++i) {
 		g = gcd(g, arr[i]);
 	}
 	if(g > 1) push_ans(g, m);
	for(auto it = ans.begin(); it != ans.end(); ++it) {
		printf("%d ", *it);
	}
}
