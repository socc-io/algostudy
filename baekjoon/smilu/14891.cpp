#include <bits/stdc++.h>
using namespace std;

struct Gear {
	list<int> state;
	void Init(const char* seed) {
		for (int i = 0; i < 8; i++) {
			state.push_back((int) seed[i] == '1');
		}
	};
	void Rotate(int wise) {
		if (wise == 1) ClockRotate();
		else CounterClockRotate();
	}
	void ClockRotate() {
		int b = state.back();
		state.pop_back();
		state.push_front(b);
	}
	void CounterClockRotate() {
		int f = state.front();
		state.pop_front();
		state.push_back(f);
	}
	int Right() const {
		auto it = state.begin();
		it++; it++;
		return *it;
	}
	int Left() const {
		auto it = state.rbegin();
		it++;
		return *it;
	}
	int Top() const {
		return state.front();
	}
	bool operator ^ (const Gear & g) const {
		return Right() != g.Left();
	}
};

struct Env {
	Gear gears[4];
	void RotateGear(int index, int from, int wise) {
		if (index > 0 && index-1 != from && gears[index-1] ^ gears[index])
			RotateGear(index - 1, index, -wise);
		if (index < 3 && index+1 != from && gears[index] ^ gears[index+1])
			RotateGear(index + 1, index, -wise);
		gears[index].Rotate(wise);
	}
	int GetScore() const {
		int ans = 0;
		for (int i = 0; i < 4; i++)
			ans |= gears[i].Top() << i;
		return ans;
	}
} env;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for (int i = 0; i < 4; i++) {
		string s; cin >> s;
		env.gears[i].Init(s.data());
	}
	
	int k; cin >> k;
	while (k--) {
		int x, y; cin >> x >> y;
		env.RotateGear(x-1, -1, y);
	}
	
	cout << env.GetScore() << '\n';
	
	return 0;
}
