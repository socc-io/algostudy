#include <stdio.h>

int main(){
	int change;
	int q,d,n,p;
	scanf("%d",&change);
	q = change/25;
	change%=25;
	d = change/10;
	change%=10;
	n = change/5;
	p = change%5;

	printf("%d QUARTER(S), %d DIME(S), %d NICKEL(S), %d PENNY(S)",q,d,n,p);
	return 0;
}