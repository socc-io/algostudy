#include <iostream>
#include <vector>

using namespace std;

inline int max(int a, int b) {
	return a < b ? b : a;
}

void DO()
{
	int a, b, c;
	int n;
	cin >> n;
	int sum = 0;
	for(int i=0;i<n;++i) {
		cin >> a >> b >> c;
		int m = max(max(a, b), c);
		sum += max(m, 0);
	}
	cout << sum << endl;
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