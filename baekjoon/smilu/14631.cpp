#include <iostream>
#include <map>
#include <cstring>

using namespace std;

#define INF (0x7FFFFFFF)

const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
const int gnd_checker_dest = (1 << 20) - 1;

char tile[4][6];
int gnd_cnt;
int mark_cnt;
int answer;

int start_pos[2];

int search_depth;
int tracking_mark;
int gnd_checker;

map<int, int> S;

bool search(int x, int y)
{	
	int nx, ny, prev_gnd_checker, prev_tracking_mark;
	int S_key;
	map<int, int>::iterator S_it;
	char nc, c;

	c = tile[x][y];

	//
	// visit
	//

	++search_depth;

	prev_tracking_mark = tracking_mark;
	if(c - '0' == tracking_mark) {
		tracking_mark++;
	}

	prev_gnd_checker = gnd_checker;
	gnd_checker |= (1 << ((x * 5) + y));

	if(gnd_checker == gnd_checker_dest) {
		if(answer > search_depth) {
			answer = search_depth;
		}
		--search_depth;
		gnd_checker = prev_gnd_checker;
		return true;
	}

	S_key = gnd_checker | (((x * 5) + y) << 20);
	if((S_it = S.find(S_key)) != S.end()) {
		if(search_depth < S_it->second) {
			S_it->second = search_depth;
		} else {
			--search_depth;
			gnd_checker = prev_gnd_checker;
			return false;
		}
	} else {
		S[S_key] = search_depth;
	}

	//
	// search
	// 

	for(int dir_idx = 0; dir_idx < 4; ++dir_idx)
	{
		nx = x + dir[dir_idx][0]; ny = y + dir[dir_idx][1];
		nc = tile[nx][ny];

		if(nx < 0 || nx >= 4 || ny < 0 || ny >= 5) {
			continue;
		}

		if(nc == '.') {
			continue;
		}

		if('0' <= nc && nc <= '0' + 20 && (nc - '0') > tracking_mark) {
			continue;
		}

		search(nx, ny);
	}

	//
	// go back
	//

	--search_depth;
	gnd_checker = prev_gnd_checker;
	tracking_mark = prev_tracking_mark;

	return false;
}

void do_task()
{
	char c;
	gnd_cnt = 0;
	mark_cnt = 0;
	gnd_checker = 0;

	//
	// get input
	//

	getchar();
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 5; ++j) {
			c = getchar();
			if(c == '#') {
				gnd_cnt++;
			}
			else if(c == '.') {
				gnd_checker |= (1 << ((i * 5) + j));
			}
			else if('0' < c && c <= '9') {
				gnd_cnt++;
				mark_cnt++;
			}
			else if('A' <= c && c <= 'Z') {
				c += ('0' + 10) - 'A';
				gnd_cnt++;
				mark_cnt++;
			}
			else if(c == '0') {
				start_pos[0] = i;
				start_pos[1] = j;
				mark_cnt++;
			}
			tile[i][j] = c;
		}
		tile[i][5] = '\0';
		getchar();
	}

	//
	// calculate
	//

	answer = INF;

	search_depth = 0;
	tracking_mark = 1;
	S.clear();
	search(start_pos[0], start_pos[1]);

	if(answer == INF) {
		answer = 0;
	}

	//
	// print
	//

	printf("%d\n", answer - 1);
}

int main(void)
{
	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	for(int i = 0; i < T; ++i) {
		do_task();
	}

	return 0;
}