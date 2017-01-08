#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

int main(void)
{
	int n, m;
	int **arr;
	scanf("%d%d", &n,&m);
	arr = new int*[n];
	for(int i=0;i<n;++i) arr[i] = new int[m];

	

	for(int i=0;i<n;++i) delete[] arr[i];
	delete[] arr;
}