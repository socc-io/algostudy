#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int getLIS(vector<int> arr)
{
	int n = arr.size();
	vector<int> lis(n, 1);
	int res = 1;
	for(int i=1; i<n; ++i) {
		for(int j=0; j<i; ++j) {
			if(arr[j] < arr[i] && lis[j]+1 > lis[i]) {
				lis[i] = lis[j]+1;
			}
		}
		if(res < lis[i]) res = lis[i];
	}
	return res;
}

int main(void)
{
	int N;
	scanf("%d", &N);
	vector< pair<int, int> > points(N);
	for(int i=0; i<N; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		points[i].first = x;
		points[i].second = y;
	}
	sort(points.begin(), points.end());
	vector<int> arr(N);
	for(int i=0; i<N; ++i) {
		arr[i] = points[i].second;
	}
	printf("%d", N-getLIS(arr));
}