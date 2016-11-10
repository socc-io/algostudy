#include <stdio.h>
#include <string.h>

int main(void)
{
	int T;
	char command[100000];
	char arrstring[400000];
	int arr[100000];
	int arrsize;
	int c_arrsize;
	scanf("%d", &T);
	for(int testidx=0; testidx<T; ++testidx) {
		scanf("%s %d %s", command, &c_arrsize, arrstring);
		int len_arrstring = strlen(arrstring);
		int len_command = strlen(command);
		int inter = 0;
		int rev = 0;
		arrsize = 0;
		if(len_arrstring > 2){
			for(int charidx=1; charidx<len_arrstring; ++charidx) {
				char val = arrstring[charidx];
				if('0' <= val && val <= '9') {
					inter = inter * 10 + (val - '0');
				}
				else {
					arr[arrsize++] = inter;
					inter = 0;
				}
			}
		}
		if(arrsize != c_arrsize) {
			printf("error");
			if(testidx < T-1) printf("\n");
			continue;
		}
		int start = 0;
		int end = arrsize;
		int forceend = 0;
		for(int charidx=0; charidx<len_command; ++charidx) {
			int val = command[charidx];
			if(val == 'R') {
				rev = (rev == 0 ? 1 : 0);
			}
			else if(val == 'D'){ // D
				if(start >= end) {
					printf("error");
					if(testidx < T-1) printf("\n");
					forceend = 1;
					break;
				}
				if(rev == 0) start++;
				else end--;
			}
			else {
				printf("error");
				if(testidx < T-1) printf("\n");
				forceend = 1;
				break;
			}
		}
		if(forceend) continue;
		if(rev == 0) {
			printf("[");
			for(int i=start;i<end;++i) {
				printf("%d", arr[i]);
				if(i != end-1) printf(",");
			}
			printf("]");
		}
		else {
			printf("[");
			for(int i=end-1;i>=start;--i) {
				printf("%d", arr[i]);
				if(i != start) printf(",");
			}
			printf("]");
		}
		if(testidx < T-1) printf("\n");
	}

	return 0;
}