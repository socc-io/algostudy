#include <cstdio>
#include <deque>

using namespace std;

bool sq[100001];
bool sqi[100000];
pair<int, int> q[100000];

int main(void)
{
	int N;
	scanf("%d", &N);
	for(int i=1; i*i <= N; ++i) { sq[i*i] = true; }
	if(sq[N]) { puts("1"); return 0; }
	q[0] = {N, 1};
	int fi = 0, bi = 1;
	for(;;) {
		auto f = q[fi++]; ++f.second;
		for(int i=1;;++i) {
			int w = f.first - i*i;
			if(w <= 0) break;
			if(sq[w]) { printf("%d", f.second); return 0; }
			if(sqi[w]) continue;
			sqi[w] = true;
			q[bi++] = {w, f.second};
		}
	}
}