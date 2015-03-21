#include <stdio.h>

int main(){
	int i,j;
	int flag = 0;
	int fake[3] = {1,0,0 };
	int temp;
	char hi[51];
	scanf("%s",&hi);
	while('\0' != hi[flag]){
		if(hi[flag] == 'A'){
			temp = fake[0];
			fake[0] = fake[1];
			fake[1] = temp;
		}
		else if(hi[flag] == 'B'){
			temp = fake[1];
			fake[1] = fake[2];
			fake[2] = temp;
		}
		else if(hi[flag] == 'C'){
			temp = fake[0];
			fake[0] = fake[2];
			fake[2] = temp;
		}
		flag ++;

	}
	for(int i=0;i<3;i++){
		if(fake[i] == 1)
			printf("%d",i+1);
	}
	return 0;
}