#include <cstdio>

const int cuts[] = {90, 80, 70, 60};

int main(void)
{
	int score;
	scanf("%d", &score);
	for(int i=0;i<4;++i){
		if(score >= cuts[i]) {
			putchar('A' + i );
			return 0;
		}
	}
	putchar('F');
}