#include<iostream>
using namespace std;

typedef pair<int, int> person;

int n;
person p[50];

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%d%d", &(p[i].first), &(p[i].second));
    }
    for(int i=0; i<n; ++i) {
        int cnt = 0;
        for(int j=0; j<n; ++j) {
            if(p[i].first < p[j].first &&
                p[i].second < p[j].second) {
                ++cnt;
            }
        }
        printf("%d ", cnt+1);
    }
}

