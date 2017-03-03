// 문자열 뒤집기
// 자료구조 스택 사용해서 풀어보기.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main(){
    string sentence;
    getline(cin, sentence);
    
    int sentenceLength;
    sentenceLength = sentence.length();
    stack <char> stk;
    
    for(int i=0; i<sentenceLength; i++){
        stk.push(sentence[i]);
    }
    for(int j=0; j<sentenceLength; j++){
        cout << stk.top();
        stk.pop();
    }
}

