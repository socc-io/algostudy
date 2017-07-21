#include <cstdio>
#include <cstring>

int stone[100];
int stone_state[100];
int sec_num;
float money;

char sbuf[100];

int main(void)
{
	int tmp;

	scanf("%d%d", &tmp, &sec_num);

	money = tmp;

	memset(stone, 0, sizeof(stone));
	memset(stone_state, 0, sizeof(stone_state));

	for(int i=0; i<sec_num; ++i) {
		scanf("%d%s", &tmp, sbuf);
		--tmp;
		stone_state[tmp] = (sbuf[0] == 'R' ? 1 : -1);
	}

	int k = 0;
	for(int i=0; i<100; ++i) {
		stone[i] += k;
		if(stone_state[i] == 1) {
			k++;
		}
	}

	k = 0;
	for(int i=99; i>=0; --i) {
		stone[i] += k;
		if(stone_state[i] == -1) {
			k++;
		}
	}

	int cnt[3] = {0, 0, 0};
	for(int i=0; i<100; ++i) {
		cnt[stone[i] % 3]++;
	}

	float res[3];
	for(int i=0; i<3; ++i) {
		res[i] = money * cnt[i] / 100;
	}

	printf("%.2f\n%.2f\n%.2f\n", res[0], res[1], res[2]);

	return 0;
}