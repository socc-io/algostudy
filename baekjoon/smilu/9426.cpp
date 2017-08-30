#include <iostream>
#include <set>
#include <queue>

using namespace std;

int N, K, tmp, mid;
long long sum;

struct Middler
{
	multiset<int> left;
	multiset<int> right;
	int mid()
	{
		if(left.size() == 0) return -1;
		auto it = left.end(); --it;
		return *it;
	}
	void shift_right()
	{
		auto it = left.end(); --it;
		right.insert(*it);
		left.erase(it);
	}
	void shift_left() {
		auto it = right.begin();
		left.insert(*it);
		right.erase(it);
	}
	void push(int val)
	{
		int m = mid();
		if(m == -1 || val <= m) {
			left.insert(val);
			while(left.size() - 1 > right.size()) shift_right();

		} else {
			right.insert(val);
			while(left.size() < right.size()) shift_left();
		}
	}
	void erase(int val)
	{	
		if(val <= mid()) {
			left.erase(val);
			while(left.size() < right.size()) shift_left();
		}
		else {
			right.erase(val);
			while(left.size() - 1 > right.size()) shift_right();
		}
	}
};

int main(void)
{
	scanf("%d%d", &N, &K);

	queue<int> Q;
	Middler M;

	for(int i = 0; i < N; ++i) {
		scanf("%d", &tmp);

		M.push(tmp);
		Q.push(tmp);

		if(i + 1 >= K) {
			sum += M.mid();

			int del = Q.front();
			Q.pop();
			M.erase(del);
		}
	}

	printf("%lld", sum);
}