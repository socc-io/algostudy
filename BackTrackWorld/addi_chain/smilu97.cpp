#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITE 999999

vector<int> arr;
int min_len = INFINITE;
vector<int> bestarr;
int dest;

void DFS()
{
	if (arr.size() > min_len) return;
	int last = *(arr.rbegin());
	if (last > dest) {
		return;
	}
	if (last == dest) {
		if (min_len > arr.size()) {
			min_len = arr.size();
			bestarr = arr;
		}
		return;
	}
	for (int i = arr.size()-1; i >= 0; --i) {
		arr.push_back(last + arr[i]);
		DFS();
		arr.pop_back();
	}
}
int main(void) {
	cin >> dest;
	arr.reserve(200);
	bestarr.reserve(200);
	arr.push_back(1);
	DFS();
	for (int i = 0; i < bestarr.size(); ++i) {
		cout << bestarr[i] << " ";
	}
	cout << endl;
	return 0;
}