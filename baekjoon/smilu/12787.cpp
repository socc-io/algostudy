#include <iostream>
#include <string.h>

using namespace std;

void strToIp(char* str)
{
	int len = strlen(str);
	unsigned long long res = 0;
	int atoicur = 0;
	for(int i=0;i<len;++i) {
		char val = str[i];
		if(val != '.') {
			atoicur = atoicur * 10 + (val - '0');
		}
		else {
			res = (res << 8) + atoicur;
			atoicur = 0;
		}
	}
	res = (res << 8) + atoicur;
	cout << res << endl;
}

void ipToStr(unsigned long long val)
{
	int res[8];
	for(int i=7;i>=0;--i) {
		res[i] = (val & 255);
		val >>= 8;
	}
	for(int i=0;i<8;++i) {
		cout << res[i];
		if(i != 7) {
			cout << '.';
		}
	}
	cout << endl;
}

void DO() {
	int a;
	unsigned long long val;	
	char str[100];
	cin >> a;
	if(a == 1) {
		cin >> str;
		strToIp(str);
	}
	else if(a == 2) {
		cin >> val;
		ipToStr(val);
	}
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