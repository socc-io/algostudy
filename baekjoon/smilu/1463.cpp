#include <iostream>

using namespace std;

#define STACK_SIZE 10000

struct cv {
	int cost;
	long long value;
	void set(int _cost, int _value) {
		cost = _cost;
		value = _value;
	}
	cv() {
	}
};

int main(void)
{
	cv stack[STACK_SIZE]; // first : cost, second : value
	cv last;
	int next_cost;
	int sp = 0; // stack pointer
	long long N;
	cin >> N;
	stack[sp++].set(0,N);
	int mincost = 999999;
	while(sp > 0) { // until stack is empty
		last = stack[--sp];
		if(last.cost >= mincost) {
			continue;
		}
		if(last.value == 1) {
			if(last.cost < mincost) {
				mincost = last.cost;
			}
			continue;
		}
		next_cost = last.cost + 1;
		stack[sp++].set(next_cost, last.value-1);
		if((last.value & 1) == 0) {
			stack[sp++].set(next_cost, last.value >> 1);
		}
		if(last.value % 3 == 0) {
			stack[sp++].set(next_cost, last.value / 3);
		}
	}
	cout << mincost << endl;
	return 0;
}