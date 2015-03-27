#include <stdio.h>
#include <string.h>
int main(){
	int n;
	int num;
	int sum;
	char ch;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		sum=0;
		while(1){
			scanf("%d",&num);
			sum += num;
			scanf("%c",&ch);
			if(ch == '\n')
				break;
		}
		printf("%d\n",sum);
	}
	return 0;
}