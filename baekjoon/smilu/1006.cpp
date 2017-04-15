#include <cstdlib>
#include <cstdio>
#include <algorithm>

#define LINK_NULL -1
#define LINK_ABANDON -2

int N, W;
int enemy_num[20000];
int link[20000];
int connect_num = 0;

int next(int pos)
{
	if(pos < N) return ((pos+1)%N);
	else        return ((pos+1)%N)+N;
}
int prev(int pos)
{
	if(pos < N) return ((pos+N-1)%N);
	else        return ((pos+N-1)%N)+N;
}
int oppo(int pos)
{
	if(pos < N) return pos+N;
	else        return pos-N;
}
bool isAdjacent(int a, int b)
{
	if(next(a) == b) return true;
	if(next(b) == a) return true;
	if(oppo(a) == b) return true;
	return false;
}

bool connect(int pos)
{
	int other, compet;
	if(link[pos] != LINK_NULL) return false;
	int others[] = { next(pos), prev(pos), oppo(pos) };
	link[pos] = LINK_ABANDON;
	for(int other_idx=0; other_idx<3; ++other_idx) {
		other = others[other_idx];
		compet = link[other];
		if(compet == LINK_ABANDON) continue;
		if(enemy_num[pos] + enemy_num[other] > W) continue;
		if(compet == LINK_NULL) {
			link[pos]   = other;
			link[other] = pos;
			return true;
		}
		else { // competition
			link[other]  = LINK_ABANDON;
			link[compet] = LINK_NULL;
			if(connect(compet)) { // check yieldable
				link[pos]   = other;
				link[other] = pos;
				return true;
			}
			else {
				link[other]  = compet;
				link[compet] = other;
			}
		}
	}
	link[pos] = LINK_NULL;
	return false;
}

void run()
{
	scanf("%d%d", &N, &W);
	for(int i=0; i<N; ++i) { // get input
		scanf("%d", enemy_num+i);
	}
	for(int i=0; i<N; ++i) {
		scanf("%d", enemy_num+N+i);
	}
	for(int i=0; i<(N<<1); ++i) { // initialize link
		link[i] = LINK_NULL;
	}
	while(true) {
		bool flag = false;
		for(int i=0; i<(N<<1); ++i) {
			if(connect(i)) {
				flag = true;
			}
		}
		if(!flag) break;
	}
	connect_num = 0;
	for(int i=0; i<(N<<1); ++i) {
		if(link[i] != LINK_NULL && link[i] != LINK_ABANDON) ++connect_num;
	}
	printf("%d\n", (N<<1)-(connect_num>>1));
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for(int i=0; i<T; ++i) {
		run();
	}
	return 0;
}