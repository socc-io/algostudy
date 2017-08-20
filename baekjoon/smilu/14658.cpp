#include <cstdio>
#include <map>

using namespace std;

struct PIICC {
	bool operator()(const pair<int, int> &A, const pair<int, int> &B) const {
		return A.first < B.first;
	}
};

struct PPIIICC {
	bool operator()(const pair< pair<int, int>, int > &A, const pair< pair<int, int>, int > &B) const {
		return A.second < B.second;
	}
};

int N, M, L, K;
int star_x, star_y;

map< pair<int, int>, int, PIICC > cost[500001];

inline int max(int a, int b)
{
	if(a < b)
		return b;
	return a;
}

int main(void)
{
	scanf("%d%d%d%d", &N, &M, &L, &K);

	for(int i = 0; i < N; ++i) {
		cost[i][{0, M + 1}] = 0;
	}

	for(int i = 0; i < K; ++i) {
		scanf("%d%d", &star_x, &star_y);

		for(int x = max(star_x - L, 0); x <= star_x; ++x) {
			int sy = max(star_y - L, 0), ey = star_y + 1;

			auto lo = cost[x].lower_bound({sy, ey});

			if(lo != cost[x].begin()) lo--;

			auto cur = lo;

			while(cur != cost[x].end() && cur->first.first < ey) {
				int cs = cur->first.first;
				int ce = cur->first.second;
				int cv = cur->second;
				auto next_cur = cur;
				next_cur++;

				// printf("x: %d, sy: %d, ey: %d, cs: %d, ce: %d, cv: %d\n", x, sy, ey, cs, ce, cv);

				if(cs < sy && ce > sy && ce <= ey) { // left half duplication
					// printf("left half\n");
					cost[x].erase(cur);
					cost[x][{cs, sy}] = cv;
					cost[x][{sy, ce}] = cv + 1;
				}
				else if(cs <= sy && ce >= ey) { // including
					// printf("including\n");
					cost[x].erase(cur);
					if(cs != sy) cost[x][{cs, sy}] = cv;
					cost[x][{sy, ey}] = cv + 1;
					if(ey != ce) cost[x][{ey, ce}] = cv;
				}
				else if(cs >= sy && cs < ey && ce > ey) { // right half duplication
					// printf("right half\n");
					cost[x].erase(cur);
					cost[x][{cs, ey}] = cv + 1;
					cost[x][{ey, ce}] = cv;
				}
				else if(cs >= sy && ce <= ey) { // included
					// printf("included\n");
					(cur->second)++;
				}
				cur = next_cur;
			}

			cur = cost[x].lower_bound({sy, ey});

			if(cur != cost[x].begin()) --cur;

			while(cur != cost[x].end() && cur->first.first < ey) {
				auto next = cur;
				++next;
				if(next == cost[x].end()) break;
				if(cur->second == next->second) {
					auto nnext = next;
					++nnext;
					int ps = cur->first.first, pe = next->first.second;
					int pv = cur->second;
					cost[x].erase(cur);
					cost[x].erase(next);
					cost[x][{ps, pe}] = pv;
					cur = nnext;
				} else {
					cur = next;
				}
			}
		}
	}

	int max_reflection = 0;
	for(int i = 0; i <= N; ++i) {
		for(auto it = cost[i].begin(); it != cost[i].end(); ++it) {
			if(max_reflection < it->second) {
				max_reflection = it->second;
			}
		}
	}

	printf("%d", K - max_reflection);

	return 0;
}