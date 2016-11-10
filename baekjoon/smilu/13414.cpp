#include <stdio.h>

bool check[100000000] = {0};
int arr[500000];
int arr2[500000];
int arr2_idx = 0;
int main()
{
	int k, l, i, lb;
	scanf("%d%d", &k, &l);
	for(i=0;i<l;++i) scanf("%d", &arr[i]);
	for(i=l-1;i>=0;--i) {
		int val = arr[i];
		if(!check[val]) {
			check[val] = true;
			arr2[arr2_idx++] = val;
		}
	}
	lb = arr2_idx - k;
	lb = lb < 0 ? 0 : lb;
	for(i=arr2_idx-1;i>=lb;--i) {
		printf("%.8d\n", arr2[i]);
	}
	return 0;
}