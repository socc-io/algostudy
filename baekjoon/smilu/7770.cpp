#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;

int main(int argc, char** argv)
{
	ull n, stage_need, all_need, stage_2;
	int stage;
	cin >> n;
	stage_need = 1;
	all_need = 0;
	for(stage=1; all_need <= n;++stage) {
		stage_need += (stage<<2) - 4;
		all_need += stage_need;
	}
	cout << stage - 2 << endl;
	return 0;
}