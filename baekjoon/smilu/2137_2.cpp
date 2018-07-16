
#include <stdio.h>
#include <math.h>

#define MAX 32767

typedef unsigned long long ull;

ull gcd(ull a, ull b) {
	ull tmp;

	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}

	while(b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return a;
}

class Fraction
{
public:
	ull up, down;
	Fraction(ull up = 0, ull down = 1):up(up),down(down) {}
	bool operator<(Fraction &b) const {
		return up * b.down < b.up * down;
	}
	Fraction operator-(Fraction &b) const {
		ull n_down
	}
};

int main(void)
{
	int a, b;

	double f_ans;
	double f_calc;

	int best_up;
	int best_down;
	double best_diff = 999999.0;

	scanf("%d%d", &a, &b);
	f_ans = (double)a / b;

	for(int i=1; i<=MAX; i++) {
		int up = (i * a + (b / 2)) / b;
		f_calc = (double)up / i;
		double diff = abs(f_calc - f_ans);
		if (diff == 0) continue;
		if(diff < best_diff) {
			best_diff = diff;
			best_up = up;
			best_down = i;
		}
	}

	printf("%d %d", best_up, best_down);

	return 0;
}
