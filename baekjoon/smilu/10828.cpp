#include <stdio.h>
#include <string.h>

int main(void)
{
	int N;
	scanf("%d", &N);
	int arr[10000];
	int idx = 0;
	char op[100];
	int a, b;
	for(int i=0;i<N;++i) {
		scanf("%s", op);
		if(strcmp(op,"push")==0) {
			scanf("%d", &a);
			arr[idx++] = a;
		}
		else if(strcmp(op,"pop")==0) {
			if(idx == 0) printf("-1\n");
			else {
				idx--;
				printf("%d\n", arr[idx]);
			}
		}
		else if(strcmp(op,"size")==0) {
			printf("%d\n", idx);
		}
		else if(strcmp(op,"empty")==0) {
			printf("%d\n", idx==0 ? 1 : 0);
		}
		else if(strcmp(op,"top")==0) {
			if(idx == 0) printf("-1\n");
			else {
				printf("%d\n", arr[idx-1]);
			}
		}
	}
}