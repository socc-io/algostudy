#include <cstdio>
#include <cstring>

const int size[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};

int main(void)
{
	char display[20];

	scanf("%s", display);

	int cost = 0;
	int len = strlen(display);

	for(int i = 0; i < len; ++i) {
		display[i] -= '0';
	}

	cost -= size[display[len - 1]];
	display[len - 1] = (display[len - 1] + 1) % 10;
	cost += size[display[len - 1]];

	int time_cnt = 1;

	while(cost != 0) {

		// make next display
		for(int i = len - 1; i >= 0; --i) {
			cost -= size[display[i]];
			display[i]++;
			if(display[i] >= 10) {
				display[i] = 0;
				cost += size[0];
			} else {
				cost += size[display[i]];
				break;
			}
		}

		++time_cnt;
	}

	printf("%d", time_cnt);

	return 0;
}