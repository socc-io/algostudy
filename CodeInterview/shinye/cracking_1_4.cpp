// 주어진 문자열 내의 모든 공백을 ‘%20’으로 바꾸는 메서드를 작성하라.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(){
    string sentence1, sentence2;
    getline(cin, sentence1);
    sentence2 = "";
    int length = sentence1.length();
    
    for(int i=0; i<length; i++){
        if(sentence1[i] == ' '){
            sentence2+="%20";
        } else{
            sentence2+=sentence1[i];
        }
    }
    cout << "new sentence : " << sentence2 << endl;
    
    return 0;
}

