#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

int pi(int n) {
  if (n == 0) return 0;
  return n - 1;
}

char p(int n) {
  if (n & 1) return 'O';
  return 'I';
}

int kmp(string s, int psize){
    int cnt = 0;
    int n = (int)s.size(), m = psize, j =0;
    for(int i = 0 ; i < n ; i++){
        while(j>0 && s[i] != p(j))
            j = pi(j-1);
        if(s[i] == p(j)){
            if(j==m-1){
                cnt++;
                j = pi(j);
            }else{
                j++;
            }
        }
    }
    return cnt;
}

int main(){
    int n, m;
    string s;

    scanf("%d%d", &n, &m);
    cin >> s;

    int res = kmp(s, 2*n+1);

    printf("%d", res);
}