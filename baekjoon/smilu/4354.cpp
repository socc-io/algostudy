#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    while(1) {
        string s;
        cin >> s;
        if(s[0] == '.') break;
        int n = s.size();
        vector<int> primes;
        vector<int> n_primes;
        for(int i=1; i*i <= n; ++i) {
            if(n%i != 0) continue;
            int na = n/i;
            primes.push_back(i);
            if(i*i != n) n_primes.push_back(na);
        }
        reverse(n_primes.begin(), n_primes.end());
        primes.insert(primes.end(), n_primes.begin(), n_primes.end());
        int ans;
        for(auto it = primes.begin(); it != primes.end(); ++it) {
            int i = *it;
            int na = n/i;
            bool fail = false;
            for(int j=i; j<n; j+=i) {
                bool same = true;
                for(int k=0; k<i; ++k) {
                    if(s[k] != s[j+k]) {
                        same = false;
                        break;
                    }
                }
                if(!same) {
                    fail = true;
                    break;
                }
            }
            if(!fail) {
                ans = na;
                break;
            }
        }
        printf("%d\n", ans);
    }
}
