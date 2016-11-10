#include <stdio.h>

int main(void)
{
	int n;
	int arr[500][500];
	int mrr[500][500];
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		for(int j=0;j<=i;++j) {
			scanf("%d", &arr[i][j]);
		}
	}
	mrr[0][0] = arr[0][0];
	for(int i=1;i<n;++i) {
		mrr[i][0] = mrr[i-1][0] + arr[i][0];
		for(int j=1;j<i;++j) {
			int left = mrr[i-1][j-1];
			int right =  mrr[i-1][j];
			mrr[i][j] = (left > right ? left : right) + arr[i][j];
		}
		mrr[i][i] = mrr[i-1][i-1] + arr[i][i];
	}
	int maxval = -1;
	for(int i=0;i<n;++i) {
		int newval = mrr[n-1][i];
		if(maxval < newval) maxval = newval;
	}
	printf("%d", maxval);

	return 0;
}