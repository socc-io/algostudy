#include <stdio.h>

int main(){
	int dwarf[10];
	int sum = 0;
	int not1,not2;
	for(int i=0;i<9;i++){
		scanf("%d",&dwarf[i]);
		sum += dwarf[i];
	}
	sum -= 100;
	for(int i=0;i<8;i++){
		for(int j=i+1;j<9;j++){
			if(dwarf[i] + dwarf[j] == sum){
				not1 = i;
				not2 = j;
				break;
			}
		}
	}
	for(int i=0;i<9;i++){
		if(not1 == i || not2 == i)
			continue;
		else
			printf("%d\n",dwarf[i]);

	}

	return 0;
}