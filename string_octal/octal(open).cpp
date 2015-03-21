#include <stdio.h>
#include <string.h>
int main(){
	char bin[1000];
	char ans[1000] = {0, };
	int flag = 0;
	int tmp;
	int pri=0;
	int i,j;
	int first=0;
	scanf("%s",&bin);
	while(bin[flag] != '\0'){
		flag++;
	}
	tmp = flag%3;
	if(tmp != 0){
		for(i=0;i<3-tmp;i++){
			ans[i] = '0';
		}
		first = 3-tmp;
	}
	for(i=first,j = 0;i<flag+tmp,j< flag;i++,j++){
		ans[i] = bin[j];
	}
	//printf("%s\n",ans);
	for(i=0;i<flag+(first);i++){
		if(i%3 == 0)
			pri += (ans[i] - '0') * 4;
		else if(i%3 == 1)
			pri += (ans[i] - '0') * 2;
		else if(i%3 == 2){
			pri += (ans[i] - '0');
			printf("%d",pri);
			pri = 0;
		}

	}
	return 0;
}