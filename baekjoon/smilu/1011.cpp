#include <iostream>
#include <math.h>

using namespace std;

int main(void)
{
	int T, a, b, offset;
	cin >> T;
	for(int test_idx = 0; test_idx < T; ++test_idx)
	{
		cin >> a >> b;
		int d = b - a;
		int ds = (int)sqrt(d);
		int ds2 = ds*ds;
		int dds = d - ds2;
		if(ds2 == d) offset = 0;
		else if(dds <= ds) offset = 1;
		else offset = 2;
		printf("%d\n", ds*2-1+offset);
	}
	return 0;
}