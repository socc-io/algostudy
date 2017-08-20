#include <iostream>
#include <set>
#include <cstring>
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

char a[1001][1001];
pair<int, int> sz[501];
pair<int, pair<int, int>> query[10001];
char s[501][501][501];

int main()
{
    int N, M;
    N = _readInt();
    M = _readInt();

    int K;
    K = _readInt();

    for(int i=0; i < N; i++)
        memset(a[i], '.', M);

    for(int i=1; i <= K; i++)
    {
        sz[i].first = _readInt();
        sz[i].second = _readInt();

        for(int j=0; j < sz[i].first; j++)
        {
            char *c = s[i][j];
            int k = 0;
            while((*c++ = _read()) != '\n');
        }
    }

    int Q = _readInt();

    for(int t=1; t <= Q; t++)
    {
        int n, y, x;
        n = _readInt();
        y = _readInt();
        x = _readInt();
        query[t] = {n, {y, x}};
    }

    set<pair<int, int>> pixel[1001];
    for(int i=0; i < N; i++)
        pixel[i].insert({0, M});

    for(int t=Q; t >= 1; t--)
    {
        int n, y, x;
        n = query[t].first;
        tie(y, x) = query[t].second;

        for(int i=0; i < sz[n].first; i++)
        {
            auto lo = pixel[y + i].lower_bound({x, x + sz[n].second});
            if(lo != pixel[y + i].begin())
            {
                auto temp = lo;
                lo--;
                if(lo->second <= x)
                    lo = temp;
            }

            while(lo != pixel[y + i].end() && lo->first < x + sz[n].second)
            {
                auto cur = lo;
                int l = max(cur->first, x), r = min(cur->second, x + sz[n].second);

                memcpy(&a[y + i][l], &s[n][i][l-x], r - l);

                if(cur->first < x)
                    pixel[y + i].insert({cur->first, x});
                if(x + sz[n].second < cur->second)
                    pixel[y + i].insert({x + sz[n].second, cur->second});

                lo++;
                pixel[y + i].erase(cur);
            }
        }

    }

    for(int i=0; i < N; i++)
        puts(a[i]);
    return 0;
}