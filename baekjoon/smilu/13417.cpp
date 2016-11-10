#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
	int T; cin >> T;
	for(int idx=0; idx<T; ++idx) {
		int len; cin >> len;
		deque<char> res;
		for(int i=0;i<len;++i) {
			char val; cin >> val;
			for(int j=0;j<res.size();++j) {
				if(val < res[j]) res.push_front(val);
				else if(val > res[j]) res.push_back(val);
				else continue;
				break;
			}
			if(res.size() == i) res.push_back(val);
		}
		for_each(res.begin(), res.end(), [](char val) { cout << val; });
		cout << endl;
	}
	return 0;
}