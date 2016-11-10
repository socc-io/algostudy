#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void DO(int idx)
{
	int n;
	string s;
	cin >> n >> s;
	int l = s.size();
	for(int idx=0; idx<l; ++idx) {
		if(s[idx] == 'c') ++n;
		else if(s[idx] == 'b' && n > 0) --n;
	}
	cout << "Data Set " << idx + 1 << ":" << endl << n << endl << endl;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int i=0;i<T;++i) {
		DO(i);
	}
	return 0;
}