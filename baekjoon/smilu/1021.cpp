#include <stdio.h>

int main(void)
{
	int arrsize, objnum;
	int obj[100];
	scanf("%d %d", &arrsize, &objnum);
	int arrsize_h = arrsize / 2;
	for(int i=0;i<objnum;++i){
		scanf("%d", &obj[i]);
		obj[i] -= 1;
	}
	int objidx = 0;
	int movesum = 0;
	while(objidx < objnum) {
		int pos = obj[objidx];
		int rightneed = arrsize - pos;
		int need = pos < rightneed ? pos : rightneed;
		for(int i=objidx+1; i<objnum; ++i) {
			obj[i] -= pos + 1;
			while(obj[i] < 0) obj[i] += arrsize;
		}
		objidx++;
		movesum += need;
		arrsize--;
	}
	printf("%d", movesum);
	return 0;
}