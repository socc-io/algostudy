#include <iostream>
#include <vector>

using namespace std;

int N, M, tmp;
int power[1000];
vector<int> able[1000];

bool visit[1000];
int doer[1000];

bool dfs(int w)
{
	visit[w] = true;
	bool success = false;

	for(auto vit = able[w].begin(); vit != able[w].end(); ++vit) {
		int v = *vit;
		if(doer[v] == -1 || dfs(doer[v])) {
			doer[v] = w;
			success = true;
			break;
		}
	}

	visit[w] = false;

	return success;
}

int main(void)
{
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N; ++i) {
		scanf("%d", power + i);
		for(int j = 0; j < power[i]; ++j) {
			scanf("%d", &tmp);
			--tmp;
			able[i].push_back(tmp);
		}
	}
}