#include <cstdio>

bool selfish[10001];

char nums[5];
int D;

int main(void)
{
	for(int i=1; i <= 10000; ++i) {
		if(!selfish[i]) {
			printf("%d\n", i);
		}
		for(int i=0;;++i) {
			++nums[i];
			++D;
			if(nums[i] == 10) {
				nums[i] = 0;
				D -= 10;
			} else {
				break;
			}
		}
		selfish[i+D] = true;
	}
}