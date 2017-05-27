#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> v;
vector<int> LIS;

int getLIS()
{
	LIS.push_back(v[0]);
	for(int i=1; i<N; ++i){
	    if(LIS.back()<v[i]){
	    	LIS.push_back(v[i]);
	    }
	    else{
	        vector<int>::iterator it=lower_bound(LIS.begin(), LIS.end(), v[i]);
	        *it=v[i];
	    }
	}
	return LIS.size();
}

int main(void)
{
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		int k;
		scanf("%d", &k);
		v.push_back(k);
	}
	printf("%d", N-getLIS());
}