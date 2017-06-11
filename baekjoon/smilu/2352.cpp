#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int main(void)
{
	int N;
	scanf("%d", &N);
	vector<int> port; port.reserve(N);
	vector<int> lis; lis.reserve(N);
	vector<int> trace(N, -1);
	for(int i=0; i<N; ++i) {
		int val; 
		scanf("%d", &val);
		port.push_back(val);
	}

	lis.push_back(port[0]);
	for(int i=1; i<N; ++i) {
		if(lis.back() <= port[i]) {
			lis.push_back(port[i]);
		}
		else {
			vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), port[i]);
			(*it) = port[i];
		}
	}

	printf("%d\n", (int)lis.size());
}