#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

#define MAX_HEIGHT 20
#define MAX_WIDTH  20

#define TILE_BLANK 0
#define TILE_MINE 1
#define TILE_ENEMY 2

const int dd[4][2] = {
	{1, 0},
	{-1, 0},
	{0, 1},
	{0, -1},
};

struct coord {
	int x, y;
	coord(): x(0), y(0) {}
	coord(int x, int y): x(x), y(y) {}
	bool operator==(const coord & c) const {
		return x == c.x && y == c.y;
	}
};

struct group {
	coord c_start;
	coord c_needs[2];
	int sz;
	int cnt_needs;
	group(): sz(0), cnt_needs(0) {}
};

struct world {
	int height;
	int width;
	int tile[MAX_HEIGHT][MAX_WIDTH];
	bool visit_mem[MAX_HEIGHT][MAX_WIDTH];

	void clear_visit_mem() {
		memset(visit_mem, 0, sizeof(visit_mem));
	}

	void clear_blank_visit() {
		for (int hi = 0; hi < height; hi++) {
			for(int wi = 0; wi < width; wi++) {
				if (tile[hi][wi] == TILE_BLANK) {
					visit_mem[hi][wi] = false;
				}
			}
		}
	}

	void input() {
		scanf("%d%d", &height, &width);
		for (int hi = 0; hi < height; hi++) {
			for (int wi = 0; wi < width; wi++) {
				scanf("%d", tile[hi] + wi);
			}
		}
	}

	void extract_groups() {
		clear_visit_mem();
		vector<group> groups;
		for (int x = 0; x < height; x++) {
			for (int y = 0; y < width; y++) {
				if (visit_mem[x][y]) continue;
				if (tile[x][y] != TILE_ENEMY) continue;
				coord c(x, y);
				group g;
				extract_group(c, g);
				groups.push_back(g);
			}
		}
	}

	void extract_group(coord &c, group &g) {
		g.c_start = c;
		clear_blank_visit();
		extract_group_visit(c, g);
	}

	void extract_group_visit(coord &c, group &g) {
		if (visit_mem[c.x][c.y]) return;
		visit_mem[c.x][c.y] = true;

		if (tile[c.x][c.y] == TILE_BLANK) {
			if (g.cnt_needs < 2) {
				g.c_needs[g.cnt_needs] = c;
				g.cnt_needs++;
			}
		} else if (tile[c.x][c.y] == TILE_MINE) {
			//
		} else if (tile[c.x][c.y] == TILE_ENEMY) {
			g.sz++;
			for (int di = 0; di < 4; di++) {
				coord n(c.x + dd[di][0], c.y + dd[di][1]);

				if (n.x < 0 || n.x >= height ||
					n.y < 0 || n.y >= width) continue;

				extract_group_visit(n, g);
			}
		}
	}
};

world gw;

int main(void)
{
	gw.input();
	gw.extract_groups();

	return 0;
}