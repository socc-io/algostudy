#include <cstdio>
#include <cstdlib>

FILE* fp;
int N, M;
char tile[11][11];

void run()
{
	scanf("%d%d", &N, &M);
	for(int i=0; i<N; ++i) {
		scanf("%s", tile[i]);
	}
	
	
}

int main(void)
{
	// fp = fopen("input.txt", "r");
	int T;
	scanf("%d", &T);
	for(int test_idx=0; test_idx<T; ++test_idx) {
		run();
	}
	// fclose(fp);
	return 0;
}