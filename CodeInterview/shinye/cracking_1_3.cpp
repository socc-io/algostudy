// 문자열 두 개를 입력받아 그 중 하나가 다른 하나의 순열인지 판별하는 메서드 작성
// 문자열 두 개를 각각 정렬하여 알파벳 순으로 정렬시킨 후, 두 문자열이 같으면 순열 아니면 순열이 아닌 로직으로 판단한다.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void checkPermutation(string s1, string s2){
    string sentence1 =s1; string sentence2 = s2;
    
    sort(sentence1.begin(), sentence1.end());
    sort(sentence2.begin(), sentence2.end());
    //cout << "sentence1 : " << sentence1 << "\n";
    //cout << "sentence2 : " << sentence2 << "\n";
    //cout << "====================================== \n";
    
    if(sentence1 == sentence2){
        cout << "순열입니다" << endl;
    } else{
        cout << "순열이 아닙니다" << endl;
    }
}

int main(){
    string temp1, temp2;
    
    getline(cin, temp1);
    getline(cin, temp2);
    
    checkPermutation(temp1, temp2);
    
    return 0;
}

