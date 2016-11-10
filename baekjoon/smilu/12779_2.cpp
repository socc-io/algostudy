#include <iostream>
#include <math.h>

using namespace std;

long long gcd (long long a, long long b)
{
  long long c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}
int main(int argc, char** argv)
{
	long long a, b;
	cin >> a >> b;
	long long up = ((long long)sqrtl(b)) - ((long long)sqrtl(a));
	if(up == 0) {
		cout << 0 << endl;
		return 0;
	}
	long long down = b - a;
	long long gcd_value = gcd(down, up);
	up /= gcd_value;
	down /= gcd_value;
	cout << up << "/" << down << endl;
	return 0;
}