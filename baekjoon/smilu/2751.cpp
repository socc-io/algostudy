#include <stdio.h>

void mergeSort(int *arr, int N)
{
	int i,j,k;
	int Nm1 = N - 1;
	int minidx, minval, newval, tmp;
	int f = N / 2;
	int *s;
	if(N < 16) {
		for(i=1;i<N;++i) {
			tmp = arr[i];
			for(j=i-1;j>=0&&tmp<arr[j];--j) arr[j+1]=arr[j];
			arr[j+1] = tmp;
		}
		return;
	}
	mergeSort(arr, f);
	mergeSort(arr+f, N-f);
	s = new int[N];
	for(i=0,j=f,k=0;i<f && j<N;) {
		s[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	}
	while(i<f) s[k++] = arr[i++];
	while(j<N) s[k++] = arr[j++];
	for(i=0;i<N;++i) arr[i] = s[i];
	delete[] s;
	return;
}

int main(int argc, char** argv)
{
	int *arr, N;
	int i;
	scanf("%d", &N);
	arr = new int[N];
	for(i=0;i<N;++i) {
		scanf("%d", &arr[i]);
	}
	mergeSort(arr, N);
	for(i=0;i<N;++i) {
		printf("%d\n", arr[i]);
	}

	return 0;
}