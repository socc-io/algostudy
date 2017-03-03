#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main() {
    string origString;
    string modString = "";
    int origString_num, modString_num;
    map <char,int> alphNum;
    
    cin >> origString;
    origString_num = origString.length();
    
    for(int i=0; i<origString_num; i++){
        char temp = origString[i];
        
        if(i==0){
            alphNum[temp] = 1;
        } else {
            if(origString[i+1] == NULL){
                modString += origString[i];
                int tmp = alphNum[origString[i]];
                
                modString += to_string(tmp+1);
                break;
            }
            if(origString[i-1] != origString[i]){
                alphNum[temp] = 1;
                
                modString += origString[i-1];
                modString += to_string(alphNum[origString[i-1]]);
                
                alphNum[origString[i-1]] = 0;
            } else{
                alphNum[temp]++;
            }
        }
    }
    
    cout << "modString : " << modString << endl;
    
    return 0;
}

