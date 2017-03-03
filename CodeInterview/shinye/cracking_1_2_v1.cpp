// 문자열 뒤집기

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void reverse(string str){
    //vector <char> reverseString;
    int stringLength;
    stringLength = str.length();
    //char temp1;
    string reverseString;
    
    for(int j = stringLength-1; j>=0; j--){
        //temp1 = str[j];
        //reverseString.push_back(temp1);
        
        reverseString +=str[j];
    }
    
    cout << reverseString << endl;
    //for(int i=0; i<stringLength; i++){
    //    cout << reverseString[i];
    //}
}

int main(){
    string sentence;
    getline(cin, sentence);
    reverse(sentence);
}

