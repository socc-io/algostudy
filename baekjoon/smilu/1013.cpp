#include <cstdio>
#include <cstdlib>
#include <cstring>

char value[201];
int vlen;

int map[7][7];
int stateValue[] = {1,0,0,1,1,0,1};

void initMap()
{
	for(int i=0; i<7; ++i) for(int j=0; j<7; ++j) {
		map[i][j] = 0;
	}
	map[0][1] = 1;
	map[1][2] = 1;
	map[2][2] = 1;
	map[2][3] = 1;
	map[3][4] = 1;
	map[3][5] = 1;
	map[4][4] = 1;
	map[4][1] = 1;
	map[4][5] = 1;
	map[5][6] = 1;
	map[6][5] = 1;
	map[6][0] = 1;
}

bool check(int state, char* str)
{
	if(*str == '\0') {
		if(state == 3 || state == 4 || state == 6) return true;
		return false;
	}
	int v = (*str) - '0';
	for(int i=0; i<7; ++i) {
		if(map[state][i] && stateValue[i] == v) {
			if(check(i, str+1)) return true;
		}
	}
	return false;
}

int main(void)
{
	initMap();
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; ++i) {
		scanf("%s", value);
		vlen = strlen(value);
		int state = value[0] == '1' ? 0 : 5;
		printf("%s\n", check(state, value+1) ? "YES" : "NO");
	}
	return 0;
}