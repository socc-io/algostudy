#include <iostream>
#include <vector>

using namespace std;

int my_add(vector<int> &digits, int pos)
{
	digits[pos] += 1;
	if(digits[pos] > 9) {
		digits[pos] -= 10;
		return my_add(digits, pos+1);
	}
	return pos;
}

void DO()
{
	vector<int> digits(100, 0);
	int digit_len = 0;
	int i;
	unsigned int num;
	cin >> num;
	while(num != 0) {
		digits[digit_len++] = num % 10;
		num /= 10;
	}
	for(i=0;i<digit_len-1;++i) {
		if(digits[i] < 5) {
			digits[i] = 0;
		}
		else {
			digits[i] = 0;
			int max_len = my_add(digits, i+1);
			if(max_len > digit_len) digit_len = max_len;
		}
	}
	bool printed_not_zero = false;
	unsigned int res = 0;
	for(int j=i+1; j>=0; --j) {
		res *= 10;
		res += digits[j];
	}
	cout << res << endl;
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