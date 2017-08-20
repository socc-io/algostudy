#include <cstdio>

int main(void)
{
	int N;
	scanf("%d", &N); getchar();
	for(int n = 0; n < N; ++n) {
		char ch;
		int score = 0;
		int score_adder = 1;
		while((ch = getchar()) == 'O' || ch == 'X') {
			if(ch == 'O') {
				score += score_adder; 
				++score_adder;
			} else {
				score_adder = 1;
			}
		}
		printf("%d\n", score);
	}
}