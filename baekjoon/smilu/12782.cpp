#include <iostream>
#include <string.h>

using namespace std;

void DO() {
	char numstr[2][1000000];
	cin >> numstr[0] >> numstr[1];
	int len = strlen(numstr[0]);
	int cnt_zo = 0;
	int cnt_oz = 0;
	for(int cur=0; cur<len; ++cur) {
		if(numstr[0][cur] == '0' && numstr[1][cur] == '1') {
			++cnt_zo;
		}
		else if(numstr[0][cur] == '1' && numstr[1][cur] == '0') {
			++cnt_oz;
		}
	}
	cout << (cnt_zo > cnt_oz ? cnt_zo : cnt_oz) << endl;
}

int main(void)
{
	int T;
	cin >> T;
	for(int i=0;i<T;++i) {
		DO();
	}
	return 0;
}