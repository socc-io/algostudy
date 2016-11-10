#include <stdio.h>

// counting sort

#define MAX_NUM 10001

int main(int argc, char** argv)
{
	int count[MAX_NUM] = {0};
	int N;
	int maxnum = -1;
	int tmp;
	scanf("%d", &N);
	for(int i=0;i<N;++i) {
		scanf("%d", &tmp);
		count[tmp]++;
		if(maxnum < tmp) {
			maxnum = tmp;
		}
	}
	for(int i=0;i<=maxnum;++i) {
		int num = count[i];
		for(int j=0;j<num;++j) {
			printf("%d\n", i);
		}
	}
	
	return 0;
}