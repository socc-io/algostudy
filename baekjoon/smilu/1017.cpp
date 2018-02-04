
#include <iostream>
#include <vector>

using namespace std;

vector<bool> is_prime(2000, true);
int mat[50][50];


bool check(vector<int> &arr)
{
	int n = arr.size();
	for(int i=0; i<n; ++i) {
		for(int j=0; j<n; ++j) {
			mat[i][j] = is_prime[arr[i] + arr[j]];
		}
	}

}

void calc_prime()
{
	is_prime[0] = false;
	is_prime[1] = false;
	for(int i=2; i<2000; ++i) {
		if(is_prime[i] == false) continue;
		for(int j=i*2; j<2000; j+=i) {
			is_prime[j] = false;
		}
	}
}

int main(void)
{
	calc_prime();

	int n, tmp;
	scanf("%d", &n);
	vector<int> arr(n);
	vector<int> narr(n-2);
	for(int i=0; i<n; ++i) {
		scanf("%d", &tmp);
		arr[i] = tmp;
	}

	for(int i=1; i<n; ++i) {
		if(is_prime[arr[0]+arr[i]] == false) continue;
		int narr_idx = 0;
		for(int j=1; j<n; ++j) {
			if(i == j) continue;
			narr[narr_idx++] = arr[j];
		}
		if(check(narr)) {
			printf("%d ", arr[i]);
		}
	}

	return 0;
}