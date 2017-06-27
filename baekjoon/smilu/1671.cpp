/*
 * problem link: https://www.acmicpc.net/problem/1671
 * Author: smilu97
 * Title: 상어의 저녁식사
 * Env: C++14, Mem: up to 128MB
 */


#include <cstdio>
#include <cstdlib>

int N;
int shark_status[1000][3];
int edible[1000][1000];

int eaten_by[1000];
int trying[1000];

int try_eat(int eater)
{
	if(trying[eater]) return 0;

	trying[eater] = 1;

	for(int target=0; target<N; ++target) {
		if(edible[eater][target] == 0) continue;  // not edible!

		int pre_eater = eaten_by[target];
		if(pre_eater == -1 || try_eat(pre_eater)) {
			eaten_by[target] = eater;
			return 1;
		}
	}

	return 0;

}


int main(void)
{

	// get input
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%d%d%d", shark_status[i], shark_status[i] + 1, shark_status[i] + 2);
	}

	// check edible each other
	for(int i=0; i<N; ++i) {
		for(int j=i+1; j<N; ++j) {

			edible[i][j] = 0;
			edible[j][i] = 0;

			if(shark_status[i][0] >= shark_status[j][0] &&
				shark_status[i][1] >= shark_status[j][1] &&
				shark_status[i][2] >= shark_status[j][2]) {

				edible[i][j] = 1;

			} else if (shark_status[i][0] <= shark_status[j][0] &&
				shark_status[i][1] <= shark_status[j][1] &&
				shark_status[i][2] <= shark_status[j][2]) {

				edible[j][i] = 1;
			}
		}
	}

	for(int i=0; i<N; ++i) {
		eaten_by[i] = -1;
	}

	int eat_count = 0;

	for(int eating_idx=0; eating_idx<2; ++eating_idx) {  // able to eat at most 2
		for(int eater=0; eater<N; ++eater) {  // every sharks try to eat
			for(int i=0; i<N; ++i) {
				trying[i] = 0;
			}
			eat_count += try_eat(eater);
		}
	}

	printf("%d", N - eat_count);

	return 0;

}
