#include <stdio.h>
#include <string.h>

#pragma warning(disable:4996)

char firststr[10000];
int len_str = -1;
bool var[26];
int using_var[26];
int using_varnum = 0;

bool calc(char *str)
{
	int op[1000];
	int arg[1000];
	int op_index = 0;
	int arg_index = 0;
	bool not_trigger = false;
	char str2[1000];
	int str2_index = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		char c = str[i];
		if ('a' <= c && c <= 'z') {
			if (not_trigger) {
				arg[arg_index++] = !var[c - 'a'];
				not_trigger = false;
			}
			else arg[arg_index++] = var[c - 'a'];
		}
		else if (c == '~') not_trigger = true;
		else if (c == '&' || c == '|') op[op_index++] = c;
		else if (c == '(') {
			str2_index = 0;
			int bopen_count = 1;
			for (int j = i + 1; bopen_count > 0; ++j) {
				char jc = str[j];
				if (jc == '(') ++bopen_count;
				else if (jc == ')') --bopen_count;
				str2[str2_index++] = jc;
			}
			str2[str2_index - 1] = '\0';
			i += str2_index;
			bool bc = calc(str2);
			if (not_trigger) {
				arg[arg_index++] = !bc;
			}
			else arg[arg_index++] = bc;
		}
	}
	while (arg_index > 1) {
		arg[arg_index - 2] = op[op_index - 1] == '&' ? arg[arg_index - 2] & arg[arg_index - 1] : arg[arg_index - 2] | arg[arg_index - 1];
		--arg_index;
		--op_index;
	}
	return arg[0];
}

int ref_i = 0;
int result[15];
int result_index = 0;
bool stop = false;
void ref() {
	if (ref_i == -1) {
		bool r = calc(firststr);
		if (r) {
			for (int i = 0; i < 15; ++i) {
				result[i] = var[i];
			}
			result_index = 1;
			stop = true;
		}
	}
	else {
		var[using_var[ref_i--]] = false;
		ref();
		if (stop) return;
		var[using_var[ref_i + 1]] = true;
		ref();
		if (stop) return;
		++ref_i;
	}
}

void setusingvar() {
	for (int i = 0; i < 26; ++i) {
		using_var[i] = -1;
	}
	for (int i = 0; firststr[i] != '\0'; ++i) {
		char c = firststr[i];
		if ('a' <= c && c <= 'z') {
			int newu = c - 'a';
			bool check = false;
			for (int i = 0; i < using_varnum; ++i) {
				if (using_var[i] == newu) {
					check = true;
					break;
				}
			}
			if (!check) {
				using_var[using_varnum++] = newu;
			}
		}
	}
}

int main(void)
{
	scanf("%s", &firststr);
	setusingvar();
	for (int i = 0; i < 26; ++i)
	{
		var[i] = false;
	}
	ref_i = using_varnum - 1;
	ref();
	if (!result_index) {
		printf("0\n");
	}
	else
	{
		printf("1\n");
		for (int i = 0; i < 15; ++i) {
			printf("%d ", result[i]);
		}
		printf("\n");
	}
	
	return 0;
}