#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main(void)
{
	deque<int> deq;
	string cmd;
	int par;
	int n;
	cin >> n;
	for (int i = 0; i<n; ++i) {
		cin >> cmd;
		if (cmd == "push_back") {
			cin >> par;
			deq.push_back(par);
		}
		else if (cmd == "push_front") {
			cin >> par;
			deq.push_front(par);
		}
		else if (cmd == "front") {
			if (deq.empty()) cout << -1 << endl;
			else cout << deq.front() << endl;
		}
		else if (cmd == "back") {
			if (deq.empty()) cout << -1 << endl;
			else cout << deq.back() << endl;
		}
		else if (cmd == "pop_front") {
			if (deq.empty()) cout << -1 << endl;
			else {
				cout << deq.front() << endl;
				deq.pop_front();
			}
		}
		else if (cmd == "pop_back") {
			if (deq.empty()) cout << -1 << endl;
			else {
				cout << deq.back() << endl;
				deq.pop_back();
			}
		}
		else if (cmd == "size") {
			cout << deq.size() << endl;
		}
		else if (cmd == "empty") {
			cout << (deq.empty() ? 1 : 0) << endl;
		}
	}
	return 0;
}