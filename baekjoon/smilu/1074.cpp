#include <bits/stdc++.h>
using namespace std;

int main(void)
{
	int N, x, y, s = 0;
	cin >> N >> x >> y;
	for(N = (1<<N-1); N; N >>= 1) {
		s += (x >= N) * (2*N*N) + (y >= N) * (N*N);
		x %= N;
		y %= N;
	}
	cout << s;
}