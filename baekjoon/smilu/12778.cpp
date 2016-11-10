#include <iostream>
#include <string.h>

using namespace std;

char int_char(int num) {
   return 'A' + num - 1;
}
int char_int(char str) {
   return str - 'A' + 1;
}

void DO() {
	int N;
	char T;
	cin >> N >> T;
	if(T == 'C') {
		for(int i=0;i<N;++i) {
			char tmp;
			cin >> tmp;
			cout << char_int(tmp) << " ";
		}
		cout << endl;
	}
	else if(T == 'N') {
		for(int i=0;i<N;++i) {
			int tmp;
			cin >> tmp;
			cout << int_char(tmp) << " ";
		}
		cout << endl;
	}
}

int main() {
   int T;
   cin >> T;
   for(int i=0;i<T;++i) {
   	DO();
   }
   return 0;
}