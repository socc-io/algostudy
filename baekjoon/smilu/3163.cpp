#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct ant
{
    int id;
    int pos;
    int rt;
    ant(int id=0, int pos=0, int rt=0):id(id),pos(pos),rt(rt) {}
};

int main()
{
    int T;
    scanf("%d", &T);
    while(T--) {
        int N, L, k;
        scanf("%d%d%d", &N, &L, &k);
        vector<ant> ants(N);
        vector<int> times(N);
        for(int i=0; i<N; ++i) {
            int pos, id;
            scanf("%d%d", &pos, &id);
            ants[i] = ant(id, pos);
            times[i] = (id > 0 ? L-pos : pos) * (id > 0 ? 1 : -1);
        }
        sort(ants.begin(), ants.end(), [](const ant &a, const ant &b) {
            return a.pos < b.pos;
        });
        sort(times.begin(), times.end(), [](const int a, int b) {
            if((a>0 && b>0) || (a<0 && b<0)) return a>b;
            else return a<b;
        });
        for(int i=0; i<N; ++i) {
            ants[i].rt = abs(times[i]);
        }
        sort(ants.begin(), ants.end(), [](const ant &a, const ant &b) {
            return a.rt == b.rt ? a.id < b.id : a.rt < b.rt;
        });
        printf("%d\n", ants[k-1].id);
    }
}
