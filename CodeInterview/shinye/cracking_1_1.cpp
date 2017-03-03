#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void sentenceCheck(string sentence){
    char array[130];
    
    for(int i=0; i<sentence.length(); i++){
        int index = (int)sentence[i];
        
        if(array[index] == ' '){
            continue;
        }
        
        if(array[index] != NULL){
            cout << "문자열에 포함된 모든 문자들이 유일하지 않습니다." << endl;
            return;
        } else{
            array[index] = sentence[i];
        }
    }
    cout << "문자열에 포함된 모든 문자들이 유일합니다." << endl;
}

int main(){
    string sentence;
    //cin은 띄어쓰기가 있으면 종료된다~~~~그러니 띄어쓰기 있는 string은 cin을 쓰면 안돼 신예야 제발 정신좀차려...ㅠㅠ
    getline(cin, sentence);
  
    sentenceCheck(sentence);
}

