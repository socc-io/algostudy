#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

int n;
string words[100010];
vector<int> levels;
int indices[100010];
map<string, int> dict;

bool cmp_indices(int a, int b) {
    return words[a] < words[b];
}

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> words[i];
    iota(indices, indices + n, 0);
    sort(indices, indices + n, cmp_indices);
    levels.resize(n);
    for (int i = 0; i < n; i++) {
        levels[indices[i]] = i;
    }
    auto lis = LIS(levels);
    cout << lis.size() << '\n';
}
