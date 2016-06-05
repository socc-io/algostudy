#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 0x7FFFFFFF

int w[30][30]; // Contain weight of raod from x to y
int b[30]; // Contain the number of x of y
int connect[30]; // contain connected index of x
int n; // number of row, col
int sortw[30][30]; // Contain sorted w[] index

void SetSortw()
{
	for(int i=0;i<n;++i){
		int tmp[30];
		for(int j=0;j<n;++j){
			tmp[j] = w[i][j];
		}
		for(int j=0;j<n;++j){
			int best;
			int best_val = -1;
			for(int k=0;k<n;++k){
				if(best_val > tmp[k]) {
					best_val = tmp[k];
					best = k;
				}
				sortw[i][k] = best;
			}
		}
	}
}
void dfs()
{
	int finder = -1;
	for(int i=0;i<n;++i){
		if(b[i] > 1){
			finder = i;
			break;
		}
	}
	int connecteds[30];
	int connecteds_index = 0;
	for(int i=0;i<n;++i){
		if(connect[i] == finder){
			connecteds[connecteds_index++] = i;
		}
	}
	int worst_connected = -1;
	int worst_value = INFINITE;
	for(int i=0;i<connecteds_index;++i){
		if(connecteds[i] < worst_value){
			worst_value = connecteds[i];
			worst_connected = i;
		}
	}
	for(int i=0;i<n;++i){
		if(b[sortw[worst_connected][i]] == 0){
			b[connect[worst_connected]]--;
			b[sortw[worst_connected][i]]++;
			break;
		}
	}
	for(int i=0;i<n;++i){
		if(b[i] != 1) return false;
	}
	return true;
}

int main(void)
{
	cin >> n;
	for(int i=0;i<n; ++i){
		for(int j=0;j<n;++j){
			cin >> w[i][j];
		}
	}
	SetSortw();
	for(int i=0;i<n;++i){
		b[i] = 0;
	}
	for(int i=0;i<n;++i){
		int biggest = -1;
		int biggest_index = -1;
		for(int j=0;j<n;++j){
			if(w[i][j] > biggest) {
				biggest = w[i][j];
				biggest_index = j;
			}
		}
		connect[i] = biggest_index;
		b[biggest_index]++;
	}
	while(!dfs());
	for(int i=0;i<n;++i){
		cout << connectd[i] << " ";
	}
	cout<<endl;
}