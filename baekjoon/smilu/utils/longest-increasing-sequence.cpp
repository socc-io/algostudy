#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

vector<int> LIS(const vector<int>& in){ // return LIS of array 'in'
	int n = in.size();
	vector<int> parent(n+1); // parent index
	vector<pi> is; //(number, index in 'in');
	is.push_back(pi(-99999999, -1));
	for(int i=0; i<n; ++i){
		if(is.back().first < in[i]){
			parent[i] = is.back().second;
			is.push_back(pi(in[i], i));
		} else{
			auto it = lower_bound(is.begin(), is.end(), pi(in[i], i));
			parent[i] = (it-1)->second;
			*it = pi(in[i], i);
		}
	}

	vector<int> ret;
	for(int i=is.back().second; i>=0; i=parent[i])
		ret.push_back(in[i]);
	reverse(ret.begin(), ret.end());
	return ret;
}