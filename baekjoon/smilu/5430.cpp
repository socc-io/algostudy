#include <cstdio>
#include <cstdlib>
#include <vector>

char cmd_str[100001];
char arr_str[100000*3+1];
int  arr[100000];
int n;
int arr_idx;

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int case_idx=0; case_idx < T; ++case_idx) {
		scanf("%s%d%s", cmd_str, &n, arr_str);
		arr_idx = 0;
		int front_del = 0, back_del = 0;
		bool reversed = false;
		for(char* i=cmd_str; (*i) != '\0'; ++i) {
			if((*i) == 'R') {
				reversed = !reversed;
			}
			else if((*i) == 'D') {
				if(reversed) ++back_del;
				else         ++front_del;
			}
		}
		if(back_del + front_del > n) {
			printf("error\n");
			continue;
		}
		else if(back_del + front_del == n) {
			printf("[]\n");
			continue;
		}
		int integer_buf = 0;
		for(char* i=arr_str; (*i) != '\0'; ++i) {
			char ch = (*i);
			if('0' <= ch && ch <= '9') {
				integer_buf = integer_buf * 10 + (ch - '0');
			}
			else if(ch == ',' || ch == ']') {
				arr[arr_idx++] = integer_buf;
				integer_buf = 0;
			}
		}
		printf("[");
		if(reversed) {
			for(int i=n-1-back_del; i >= front_del + 1; --i) {
				printf("%d,", arr[i]);
			}
			printf("%d]\n", arr[front_del]);
		} else {
			for(int i=front_del; i<n-back_del-1; ++i) {
				printf("%d,", arr[i]);
			}
			printf("%d]\n", arr[n-back_del-1]);
		}
	}
}