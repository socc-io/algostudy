#include <iostream>
#include <vector>

using namespace std;

void func(int val)
{
	vector<int> ten_exp_remain;
	vector<int> comb[10000];
	long long ten_exp_cur = 1;
	int idx = 0;
	int finded = 0;
	while(1) {
		int now_remain = ten_exp_cur % val;
		ten_exp_remain.push_back(now_remain);
		ten_exp_cur *= 10;
		if(comb[now_remain].size() == 0) {
			comb[now_remain].push_back(idx);
			if(now_remain == 0) break;
		}
		for(int i=1;i<=val;++i) {
			int combisize = comb[i].size();
			if(comb[i].size() != 0) {
				if(comb[i][combisize-1] != idx) {
					int to = (i + now_remain) % val;
					if(to == 0) finded = 1;
					if(comb[to].size() == 0) {
						comb[to] = comb[i];
						comb[to].push_back(idx);
					}
				}
			}
			if(finded) break;
		}
		if(finded) break;
		idx++;
	}
	int last = comb[0][comb[0].size()-1];
	int cidx = comb[0].size()-1;
	for(int i=last;i>=0;--i) {
		if(i == comb[0][cidx]) {
			cidx--;
			printf("1");
		}
		else {
			printf("0");
		}
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	int n;
	cin >> n;
	while(n != 0) {
		func(n);
		cin >> n;
	}
	return 0;
}