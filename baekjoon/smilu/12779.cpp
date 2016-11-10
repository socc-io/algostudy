#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
	long long a, b;
	long long d;
	long long cur = 0;
	int cnt = 0;
	cin >> a >> b;
	d = b - a;
	cur = (int)sqrt(a) + 1;
	cur2 = (int)sqrt(b);
	while(cur * cur <= b) {
		++cnt;
		++cur;
	}
	if(cnt == 0) {
		cout << 0 << endl;
	}
	else { // cnt / d
		long long cnt2 = cnt / 2;
		for(long long i=2; i<= cnt2; ++i) {
			if((cnt%i) == 0 && (d%i) == 0) {
				cnt /= i;
				d /= i;
			}
		}
		cout << cnt << "/" << d << endl;
	}
	return 0;
}