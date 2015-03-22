#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    cin >> s;
    int j=0;
    string s1;
    for(int i=s.length()-1; i>=0; i--){
        j++;
        s1 = s[i]+s1;
        if(j%3==0){
            s1 = ','+s1;
        }
    }
    if(s.length()%3==0){
        s1 = s1.substr(1,s1.length()-1);
    }
    cout <<s1 << endl;
    return  0;
}
