#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	int x[10000];

	scanf("%d",&n);

	for(int i=0; i < n;i++)
		scanf("%d",&x[i]);
	
	for(int i=0; i < n; i++){
		for(int j=i; j < n;j++ )
			if(x[i] > x[j]) {
				int tmp = x[i];
				x[i] = x[j];
				x[j] = tmp;
			}
	}
	if(n%2 == 0){
		for(int i=1; i < n/2; i+=2){
			int tmp = x[i];
			x[i] = x[n-i-1];
			x[n-i-1] = tmp;
		}
	}else{
		for(int i=1; i < n/2; i+=2){
			int tmp = x[i];
			x[i] = x[n-i];
			x[n-i] = tmp;
		}
	}

	for(int i=0; i < n;i++)
		printf("%d ",x[i]);

	return 0;
}