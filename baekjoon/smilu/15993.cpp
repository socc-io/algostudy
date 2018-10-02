#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 100000
#define MOD 1000000009

typedef long long lld;

int T, N;

int maxN;
pair<lld,lld> mem[MAXN + 1];

int main(void)
{
    mem[1] = make_pair(0, 1);
    mem[2] = make_pair(1, 1);
    mem[3] = make_pair(2, 2);
    for (int i = 4; i <= MAXN; i++) {
        mem[i] = make_pair(
            mem[i - 1].second + mem[i - 2].second + mem[i - 3].second,
            mem[i - 1].first  + mem[i - 2].first  + mem[i - 3].first
        );
        mem[i].first  %= MOD;
        mem[i].second %= MOD;
    }
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &N);
        printf("%lld %lld\n", mem[N].second, mem[N].first);
    }
    return 0;
}
