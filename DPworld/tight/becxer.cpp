#include <iostream>                                                                
#include <cstdio>                                                                  
#define MAX_K 10                                                                   
#define MAX_N 101                                                                  

using namespace std;

long double tnt[MAX_K][MAX_N];

int main(void){
	int k, n;
	cin >> k >> n;
	for (int i = 0; i <= k; i++){
		tnt[i][0] = 1;
	}

	long double all = k + 1;
	for (int i = 1; i < n; i++){
		all *= (k + 1);
		for (int j = 0; j <= k; j++){
			tnt[j][i] = tnt[j][i - 1];
			if (j - 1 >= 0) tnt[j][i] += tnt[j - 1][i - 1];
			if (j + 1 <= k) tnt[j][i] += tnt[j + 1][i - 1];
		}
	}

	long double nnt = 0;
	for (int j = 0; j <= k; j++){
		nnt += tnt[j][n - 1];
	}
	printf("%.5Lf\n", (nnt * 100) / all);
}
