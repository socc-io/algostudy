#include<iostream>
#include<string>
#include<set>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    set<pair<int,int>> chk;
    for(int i=0; i<n; ++i) {
        int h1=0, h2=0;
        for(int j=i; j<n; ++j) {
            h1 = (h1 * 3137 + s[j]) % 1000000007;
            h2 = (h2 * 3137 + s[j]) % 1000007;
            chk.insert(make_pair(h1, h2));
        }
    }
    printf("%ld", chk.size());
}
