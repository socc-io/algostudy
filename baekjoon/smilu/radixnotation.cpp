#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atoi(char* str) // string -> int
{
	int str_len = strlen(str);
	int res = 0;
	for(int i=0;i<str_len; ++i) {
		res *= 10;
		res += str[i] - '0';
	}
	return res;
}

int transfer(int val, int radix, char* result)
{
	int cur = val;
	int result_idx = 0;
	while(cur != 0) {
		int val = cur % radix;
		if(0 <= val && val <= 9) {
			val = '0' + val;
		}
		else {
			val = 'A' + val - 10;
		}
		result[result_idx++] = val;
		cur /= radix;
	}
	return result_idx;
}

int main(int argc, char** argv)
{
	char str[10000];
	int radix;
	int val[1000];
	if(argc < 3) {
		printf("error\n");
		return 0;
	}
	radix = atoi(argv[1]);
	if(!(2 <= radix && radix <= 36)) {
		printf("error\n");
		return 0;
	}
	for(int i=2; i<argc; ++i) {
		val[i-2] = atoi(argv[i]);
	}
	int valnum = argc - 2;
	for(int i=0;i<valnum;++i) {
		int res_len = transfer(val[i], radix, str);
		for(int j=res_len-1; j>=0; --j) {
			printf("%c", str[j]);
		}
		printf("\n");
	}
	return 0;
}