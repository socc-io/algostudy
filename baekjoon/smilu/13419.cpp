#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int idx=0; idx<T; ++idx) {
		char str[30];
		cin >> str;
		int len = strlen(str);
		char res[30];
		int res_idx = 0;
		int cur = 0;
		while(true) {
			res[res_idx++] = str[cur];
			cur = (cur + 2) % len;
			if(res[0] == res[res_idx-1] && res_idx > 1) {
				res[res_idx-1] = '\0';
				break;
			}
		}
		cout << res << endl;
		res_idx = 0;
		cur = (1 % len);
		while(true) {
			res[res_idx++] = str[cur];
			cur = (cur + 2) % len;
			if(res[0] == res[res_idx-1] && res_idx > 1) {
				res[res_idx-1] = '\0';
				break;
			}
		}
		cout << res << endl;
	}
}