#include<iostream>
#include<vector>
using namespace std;

vector<int> edges[501];
bool visit[501];
int btime[501];
int cache[501];
int n, tmp;

int find_cost(int pos)
{
    int &ret = cache[pos];
    if(ret) return ret;
    int max_ret = 0;
    for(int next: edges[pos]) {
        max_ret = max(max_ret, find_cost(next));
    }
    return ret = max_ret + btime[pos];
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d", btime+i);
        for(scanf("%d", &tmp); tmp != -1; scanf("%d", &tmp)) {
            edges[i].push_back(tmp-1);
        }
    }
    for(int i=0; i<n; ++i) {
        printf("%d\n", find_cost(i));
    }
}
                
