#include <cstdio>
#include <cstring>

const int size[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5, 6};
const int k_dic[] = {0, 2, 4, 7};

long long pow(long long a, long long b)
{
	long long res = 1;
	while(b) {
		if(b & 1) {
			res *= a;
		}
		a *= a;
		b >>= 1;
	}
	return res;
}

int main(void)
{
	char display[20];

	scanf("%s", display);

	int cost = 0;
	int len = strlen(display);

	for(int i = 0; i < len; ++i) {
		display[i] -= '0';
	}

	long long time_cnt = 0;
	long long time_unit = 1;

	for(int c_idx = len - 1;; --c_idx) {

		int cm = (c_idx + 1 - len);
		int cM = -4 * cm;

		// printf("phase %d, cost: %d, (%d, %d)\n", len - c_idx, cost, cm, cM);

		bool found = false;
		while(true) {

			// show_display();

			if(time_cnt != 0 && cm <= cost && cost <= cM) {
				// printf("found: %d, %d\n", time_cnt, cost);
				
				if(cost < 0) {
					time_cnt += (pow(10, -cost) - 1) / 9 * 8;
				} else if (cost > 0) {
					long long o = (pow(10, cost / 4) - 1) / 9;
					long long k = cost % 4;
					if(k != 0) {
						o = o * 10 + k_dic[k];
					}
					time_cnt += o;
				}

				found = true;
				break;
			}

			for(int i = c_idx; i >= 0; --i) {
				display[i]++;
				cost += size[display[i]] - size[display[i] - 1];
				if(display[i] < 10) {
					break;
				} else {
					display[i] = 0;
				}
			}
			time_cnt += time_unit;

			if(display[c_idx] == 0) {
				break;
			}
		}

		if(found) {
			break;
		}
		time_unit *= 10;
	}

	printf("%lld", time_cnt);
}