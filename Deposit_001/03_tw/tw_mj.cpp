#include <stdio.h>
unsigned int tower[500001];
int main(){
	int num;
	int yes = 0;
	int end = 0;
	scanf("%d",&num);
	scanf("%d",&tower[0]);
	printf("0");
	for(int i=1;i<num;i++){
		scanf("%d",&tower[i]);
		if(tower[i] > tower[end]){
			end = i;
			printf(" 0");
		}
		else{
			for(int j=i;j>=end;j--){
				if(tower[i] < tower[j]){
					printf(" %d",j+1);
					break;	
				}
			}
		}
			
	}
	
	
	return 0;
}