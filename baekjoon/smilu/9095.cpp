#include <cstdio>
#include <cstdlib>

#define MAX_RESULT 20

int results[MAX_RESULT+1];

void dfs(int pos)
{
	if(pos > MAX_RESULT) return;
	results[pos]++;

	dfs(pos+1);
	dfs(pos+2);
	dfs(pos+3);
}

int main(void)
{
	for(int i=0; i<=MAX_RESULT; ++i) {
		results[i] = 0;
	}
	dfs(0);

	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		int input;
		scanf("%d", &input);
		printf("%d\n", results[input]);
	}
}