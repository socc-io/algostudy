#include <iostream>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

static char _buffer[819200];
static int _currentChar = 0;
static int _charsNumber = 0;

static inline char _read() {
    if (_currentChar == _charsNumber) {
        _charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), stdin);
        _currentChar = 0;
    }
    return _buffer[_currentChar++];
}

static inline int _readInt() {
    int c, x, s;
    c = _read();
    while (c <= 32) c = _read();
    x = 0;
    while (c > 32) {
        x *= 10;
        x += c - '0';
        c = _read();
    }
    return x;
}

class IntegerPairFirstComparator
{
public:
	bool operator()(const pair<int, int> &a, const pair<int, int> &b)
	{
		return a.first < b.first;
	}
};

typedef set< pair<int, int>, IntegerPairFirstComparator > GSet;

int N, M, K, Q;

int size[500][2];
char doj[500][500][501]; // dojang

int doj_type[10000];
int doj_pos[10000][2];

GSet G[1000];
char paper[1000][1001];

int main(void)
{
	//
	// get input
	//

	N = _readInt();
	M = _readInt();
	K = _readInt();

	for(int i = 0; i < K; ++i) {
		size[i][0] = _readInt();
		size[i][1] = _readInt();

		for(int j = 0; j < size[i][0]; ++j) {
			char *c = doj[i][j];
			while((*c++ = _read()) != '\n');
		}
	}

	Q = _readInt();

	for(int i = 0; i < Q; ++i) {
		doj_type[i] = _readInt() - 1;
		doj_pos[i][0] = _readInt();
		doj_pos[i][1] = _readInt();
	}

	//
	// initialize some variables
	//

	for(int i = 0; i < N; ++i) {
		memset(paper[i], '.', sizeof(char) * M);
		G[i].insert({0, M});
	}

	//
	// calculate
	//

	for(int q_idx = Q - 1; q_idx >= 0; --q_idx)
	{
		int type = doj_type[q_idx];
		int sx = doj_pos[q_idx][0];
		int sy = doj_pos[q_idx][1];
		int ex = sx + size[type][0];
		int ey = sy + size[type][1];

		for(int x = sx; x < ex; ++x)
		{
			GSet *g = G + x;

			GSet::iterator cur = g->lower_bound({sy, ey}), tmp;

			if(cur != g->begin())
			{
				tmp = cur;
				--cur;
				if(cur->second <= sy) {
					cur = tmp;
				}
			}

			while(cur != g->end() && cur->first < ey)
			{
				int cl = cur->first, cr = cur->second;
				int l = max(cl, sy), r = min(cr, ey);

				memcpy(&paper[x][l], &doj[type][x - sx][l - sy], r - l);

				tmp = cur;
				++cur;
				g->erase(tmp);

				if(cl < sy) {
					g->insert({cl, sy});
				}
				if(ey < cr) {
					g->insert({ey, cr});
				}
			}
		}
	}

	//
	// print
	//

	for(int i = 0; i < N; ++i) {
		puts(paper[i]);
	}
	puts("\n");
	

	return 0;
}