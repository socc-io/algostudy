#include <iostream>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	for(int test_idx = 0; test_idx < T; ++test_idx)
	{
		int a, b;
		cin >> a >> b;
		a %= 10;
		int m = a;
		for(int i=1;i<b;++i){
			m *= a;
			m %= 10;
			if(m == 0) break;
		}
		if(m == 0) m = 10;
		printf("%d\n", m);
	}
	return 0;
}