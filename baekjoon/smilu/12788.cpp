#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
	int N, M, K;
	cin >> N >> M >> K;
	int need = M * K;
	int arr[1000];
	for(int i=0;i<N;++i) {
		cin >> arr[i];
	}
	sort(arr, arr+N);
	int sum = 0;
	int cnt = 0;
	for(int i=N-1;i>=0;--i) {
		sum += arr[i];
		++cnt;
		if(sum >= need) {
			break;
		}
	}
	if(sum < need) {
		cout << "STRESS" << endl;
	}
	else {
		cout << cnt << endl;
	}
	return 0;
}