#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void DO()
{
	int size;
	string from, to;
	cin >> size >> from >> to;
	int bw = 0;
	int wb = 0;
	for(int i=0;i<size;++i) {
		if(from[i] == 'B' && to[i] == 'W') ++bw;
		else if(from[i] == 'W' && to[i] == 'B') ++wb;
	}
	cout << (bw < wb ? wb : bw) << endl;
}

int main(int argc, char** argv)
{
	int T;
	cin >> T;
	for(int i=0;i<T;++i) {
		DO();
	}
	return 0;
}