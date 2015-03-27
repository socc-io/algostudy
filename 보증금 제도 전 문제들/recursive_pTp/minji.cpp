#include <stdio.h>
int mountain(int num){
	if(num ==1) return 1;
	return mountain(num--);
}
int main(){
	int n;
	scanf("%d",&n);
	mountain(n);
}

 // 1일때   1 
 // 2일때   1+2+1 
 // 3일때는 2+3+2
 // 4일때는 3+4+3 
 // 5일떄는 4+5+4