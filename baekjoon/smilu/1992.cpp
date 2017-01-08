#include <cstdio>

int size;
char tile[65][65];
char buf[9000];
int buf_length = 0;

void convert(int unit, int from_x, int from_y)
{
	// printf("convert(%d,%d,%d)\n", unit, from_x, from_y);
	char initializer = tile[from_x][from_y];
	bool all_flag = true;
	int to_x = from_x + unit, to_y = from_y + unit;
	for(int cx = from_x; cx < to_x ; ++cx) {
		for(int cy = from_y; cy < to_y; ++cy) {
			if(tile[cx][cy] != initializer) {
				all_flag = false;
				break;
			}
		}
		if(!all_flag) {
			buf[buf_length++] = '(';
			unit >>= 1;
			convert(unit, from_x       , from_y        );
			convert(unit, from_x       , from_y + unit );
			convert(unit, from_x + unit, from_y        );
			convert(unit, from_x + unit, from_y + unit );
			buf[buf_length++] = ')';
			return;
		}
	}
	buf[buf_length++] = initializer;
}

int main(void)
{
	scanf("%d", &size);
	for(int i=0;i<size;++i) {
		scanf("%s", tile[i]);
	}
	convert(size, 0, 0);
	buf[buf_length++] = '\0'; // clearify end of string
	printf("%s", buf);
}