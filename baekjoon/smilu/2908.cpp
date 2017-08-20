#include <cstdio>

char buf[2][4]; 

int main(void)
{
	scanf("%s%s", buf[0], buf[1]);
	for(int i=2;;--i) {
		if(buf[0][i] > buf[1][i]) {
			for(int j = 2; j >= 0; --j) putchar(buf[0][j]);
			break;
		} else if(buf[0][i] < buf[1][i]) {
			for(int j = 2; j >= 0; --j) putchar(buf[1][j]);
			break; 
		}
	}
}