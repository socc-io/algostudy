#include <iostream>

using namespace std;

#define INFINITE 999999

bool check(int val, int *b, int blen)
{
	while(val != 0) {
		int a = val % 10;
		val /= 10;
		bool found = false;
		for(int i=0;i<blen;++i) {
			if(b[i] == a) {
				found = true;
				break;
			}
		}
		if(!found) {
			return false;
		}
	}
	return true;
}

int getNum(int val, int *b, int blen)
{
	int last_right_min = INFINITE;
	int min = INFINITE;
	if(check(val, b, blen)) return 0;
	for(int left=2; left<last_right_min && left < val;++left) {
		if((val%left) == 0) {
			int right = val / left;
			if(right < last_right_min) {
				last_right_min = right;
			}
			int left_val = getNum(left, b, blen);
			int right_val = getNum(right, b, blen);
			int new_val = left_val + right_val + 1;
			if(new_val < min) {
				min = new_val;
			}
		}
	}
	return min;
}

void DO() {
	int N;
	int card[10];
	int q_num;
	int q[20];
	cin >> N;
	for(int i=0;i<N;++i) {
		cin >> card[i];
	}
	cin >> q_num;
	for(int i=0;i<q_num;++i) {
		cin >> q[i];
	}
	for(int qidx=0; qidx<q_num;++qidx) {
		int val = getNum(q[qidx], card, N);
		if(val >= INFINITE) {
			cout << -1 << endl;
		}
		else {
			cout << val << endl;
		}
	}
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