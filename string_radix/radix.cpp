#include <stdio.h>

int main(){
	int i,j;
	int d,r;
	int flag=0,tmp;
	int flag1 = 0;
	char ans[20000] = {0, };
	scanf("%d %d",&d,&r);
	tmp = d;
	if(d == 1){
		printf("1");
		return 0;
	}
	while(tmp >= r){
		tmp = tmp/r;
		flag++;
	}
	tmp = d;
	if(d < r){
		if(d > 9)
			ans[flag1] = (d-10)+'A';
		else ans[flag1] = d+'0';
		printf("%c",ans[flag1]);
		return 0;
	}
	for(i=1;i<=flag;i++){
		if(i < flag){
			if(tmp % r > 9)
				ans[flag1] = (tmp%r-10)+'A';
			else ans[flag1] = tmp%r+'0';
			flag1++;
			tmp = tmp/r;
		}
		else if(i == flag){
			if(tmp % r > 9)
				ans[flag1] = (tmp%r-10)+'A';
			else ans[flag1] = tmp%r+'0';
			flag1++;
			//ans[flag1] = tmp/r+'0';
			if(tmp / r > 9)
				ans[flag1] = (tmp/r-10)+'A';
			else ans[flag1] = tmp/r+'0';
		}
	}
	for(j=flag1 ; j>=0 ; j--){
		printf("%c",ans[j]);
	}
	return 0;
}