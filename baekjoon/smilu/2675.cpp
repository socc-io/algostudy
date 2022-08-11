#include <iostream>
#include <string>
using namespace std;

void task() {
	int r;
	string s;
	cin >> r >> s;

	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < r; j++) {
			cout << s[i];
		}
	}

	cout << '\n';
}

int main() {
	int t;
	cin >> t;

	while (t--) {
		task();
	}
}
