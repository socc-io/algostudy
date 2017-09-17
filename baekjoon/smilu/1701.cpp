#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    string s;
    getline(cin, s);
    int n = s.size();
    vector<int> pi(n);
    int ans = 0;
    for(int o=0; o<n; ++o) {
        for(int i=o; i<n; ++i) pi[i] = o;
        int j=o;
        for(int i=o+1; i<n; ++i) {
            while(j > o && s[i] != s[j]) {
                j = pi[j-1];
            }
            if(s[i] == s[j]) {
                pi[i] = ++j;
                int na = pi[i] - o;
                if(ans < na) {
                    ans = na;
                }
            }
        }
    }
    printf("%d", ans);
}
