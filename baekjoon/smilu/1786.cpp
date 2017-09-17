#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

int main()
{
    string s, p;
    getline(cin, s);
    getline(cin, p);
    int n = s.size();
    int m = p.size();
    int j = 0;
    vector<int> pi(m, 0);
    for(int i=1; i<m; ++i) {
        while(j > 0 && p[i] != p[j]) {
            j = pi[j-1];
        }
        if(p[i] == p[j]) {
            pi[i] = ++j;
        }
    }
    j = 0;
    vector<int> ans;
    for(int i=0; i<n; ++i) {
        while(j > 0 && s[i] != p[j]) {
            j = pi[j-1];
        }
        if(s[i] == p[j]) {
            if(j == m-1) {
                ans.push_back(i-m+1);
                j = pi[j];
            } else {
                j++;
            }
        }
    }
    printf("%lu\n", ans.size());
    for(int i=0; i<ans.size(); ++i) {
        printf("%d ", ans[i]+1);
    }
}
