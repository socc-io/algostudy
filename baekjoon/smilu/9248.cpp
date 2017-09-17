#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

char s[500001];

int main()
{
    scanf("%s", s);
    int n = strlen(s);
    vector<int> arr(n);
    for(int i=0; i<n; ++i) arr[i] = i;
    sort(arr.begin(), arr.end(), [](int a, int b) {
        while(s[a] == s[b]) ++a, ++b;
        return s[a] < s[b];
    }); 
    for(int i=0; i<n; ++i) {
        printf("%d ", arr[i]+1);
    } putchar('\n');
}
