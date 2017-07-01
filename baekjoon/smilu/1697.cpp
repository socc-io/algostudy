#include <cstdio>
#include <cstdlib>
#include <cmath>

int src, dest;

int abs(int val) {
	if(val < 0)
		return val * (-1); 
	return val;
}

int main(void)
{
	scanf("%d%d", &src, &dest);

	int cost = 0;
	int min_cost = 0;

	int log_src  = log2(src);
	int log_dest = log2(dest);
	int log_offset = log_dest - log_src;

	if(log_offset > 0) {
		cost += abs((dest >> log_offset) - src);
		cost += log_offset;
		for(int i=0; i<log_offset; ++i) {
			if(dest & (1 << i)) {
				cost++;
			}
		}

		min_cost = cost;

		cost = 0;
		
	} else {
		cost = abs(src - dest);
	}

	printf("%d", cost);

	return 0;
}