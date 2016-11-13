#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

template <typename T> void swap(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int idx=0; idx<T; ++idx) {
		ll a, b, c;
		char op1, op2;
		ll arg1, arg2, r, rop, R;
		cin >> a >> op1 >> b >> op2 >> c;
		if(op1 == '=') {
			r = a;
			arg1 = b;
			arg2 = c;
			rop = op2;
		} else {
			r = c;
			arg1 = a;
			arg2 = b;
			rop = op1;
		}
		     if(rop == '+') R = arg1 + arg2;
		else if(rop == '-') R = arg1 - arg2;
		else if(rop == '*') R = arg1 * arg2;
		else if(rop == '/') R = arg1 / arg2;
		if(R == r) {
			cout << "correct" << endl;
		} else {
			cout << "wrong answer" << endl;
		}
	}
}