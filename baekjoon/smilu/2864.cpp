#include <iostream>

using namespace std;

const int minify[] = {0, 1, 2, 3, 4, 5, 5, 7, 8, 9};
const int maxify[] = {0, 1, 2, 3, 4, 6, 6, 7, 8, 9};

pair<int,int> get()
{
    int min=0, max=0;
    char ch;
    while((ch = getchar()) >= '0' && ch <= '9') {
        ch -= '0';
        min = min*10 + minify[ch];
        max = max*10 + maxify[ch];
    }
    return make_pair(min, max);
}

int main(void)
{
    pair<int, int> a = get(), b = get();
    printf("%d %d", a.first + b.first, a.second + b.second);
}

