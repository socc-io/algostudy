#include <stdio.h>

int main(){
	int num[4] = {0, };
	int max=0,min=101,mid;
	int addr_max,addr_min;
	char alph[4] = {0, };
	for(int i=1;i<=3;i++){
		scanf("%d",&num[i]);
		if(max < num[i]){
			max = num[i];
			addr_max = i;
		}
		if(min > num[i]){
			min = num[i];
			addr_min = i;
		}
	}
	num[addr_min] = 0;
	num[addr_max] = 0;

	for(int i=1;i<=3;i++){
		if(num[i] != 0){
			mid = num[i];
		}
	}
	scanf("%s",&alph);
	for(int i=0;i<3;i++){
		if(alph[i] == 'A')
			printf("%d ",min);
		if(alph[i] == 'B')
			printf("%d ",mid);
		if(alph[i] == 'C')
			printf("%d ",max);
	}
	
	return 0;
}