#include <iostream>
#include "fibonacci.h"

using namespace std;

int main(void)
{
	int n;
	cin >> n;
	if(n <= 0) return 0;
	for(int i=0;i<n;++i) {
		cout << fibo(i) << " ";
	}
	cout << endl;
	return 0;
}