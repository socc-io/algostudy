#include <iostream>
#include <string.h>

using namespace std;

bool isEqual(char* a, char* b, int len)
{
	for(int i=0;i<len;++i){
		if(a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int main(void)
{
	char base[100001];
	char o[11];
	cin >> base >> o;
	int base_len = strlen(base);
	int o_len = strlen(o);
	int cnt = 0;
	int bmo = base_len - o_len;
	for(int i=0;i<=bmo;++i) {
		if(isEqual(base+i, o, o_len)) {
			++cnt;
		}
	}
	cout << cnt << endl;
	return 0;
}