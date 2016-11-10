#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max(int a, int b) { return a > b ? a : b; }



int main(int argc, char** argv)
{
	int size;
	cin >> size;
	vector<int> arr(size);
	for(int i=0;i<size;++i) {
		cin >> arr[i];
	}
	int setNum;
	cin >> setNum;
	int mv = -1;
	vector<int> a_arr(setNum);
	vector<int> b_arr(setNum);
	vector<int> c_arr(setNum);
	int arr_idx = 0;
	for(int i=0;i<setNum;++i) {
		int a, b, c;
		cin >> a >> b; c = max(a, b);
		for(arr_idx=arr_idx-1; arr_idx >= 0 && c_arr[arr_idx] < c; --arr_idx) {}
		++arr_idx;
		a_arr[arr_idx] = a;
		b_arr[arr_idx] = b;
		c_arr[arr_idx] = c;
		++arr_idx;	
	}
	for(int i=0;i<arr_idx;++i) {
		if(b_arr[i] < a_arr[i]) {
			sort(arr.begin(), arr.begin() + a_arr[i]);
		}
		sort(arr.begin(), arr.begin() + b_arr[i], greater<int>());
	}
	for(int i=0;i<size;++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}