#include <iostream>
#include <fstream>
#define VERSION "s"
using namespace std;
 
 
bool ustrcmp(char* src, char* dst){
    while (*src != NULL && *dst != NULL){
        if (*src++ != *dst++) return false;
    }
    return true;
}
 
bool checkPattern(char arr[100], int count){
    bool isPatternExist = false;
    for (int i = 1; i * 2 <= count; i++){
        if (ustrcmp(&arr[count - i * 2], &arr[count - i])){
            isPatternExist = true;
        }
    }
    return isPatternExist;
}
 
int len = 0;
 
class seq{
public:
    char arr[100];
    int count;
    seq(char first ){
        count = 0;
        arr[count++] = first;
        arr[count] = NULL;
    }
 
    bool isGoal( ){
        return (count >= len) ? true : false;
    }
 
    seq* getCandidate(char next){
        seq* candy = NULL;
        arr[count] = next;
        arr[count + 1] = NULL;
        if (!checkPattern(arr, count + 1)){
            candy = new seq(0);
            for (int i = 0; i < count; i++) {
                candy->arr[i] = this->arr[i];
            }
            candy->count = this->count;
            candy->arr[candy->count++] = next;
            candy->arr[candy->count] = NULL;
        }
        return candy;
    }
};
 
template<typename T>
class stack{
public:
    T arr[100000];
    int top;
    stack( ){ top = 0; }
    void push(T item){ arr[top++] = item; }
    T pop( ) { return arr[--top]; }
    bool isEmpty( ){ return (top == 0) ? true : false; }
};
 
int solution(istream& in, ostream& out){
    in >> len;
    stack<seq*> st = stack<seq*>( );
 
    for (int i = 2; i >= 0; i--){
        seq* first = new seq((char)('1' + i));
        if (first != NULL) st.push(first);
    }
 
    while (true){
        if (st.isEmpty( )) break;
        seq* now = st.pop( );
        if (now->isGoal( )){
            out << now->arr << endl;
            break;
        }else{
            for (int i = 2; i >= 0; i--){
                seq* candy = now->getCandidate((char)('1'+i));
                if (candy != NULL) {
                    st.push(candy);
                }
            }
        }
        delete(now);
    }
    return 0;
}
 
 
int main(void){
    istream* is = &cin;
    ostream* os = &cout;
    ifstream ifs;
    ofstream ofs;
    if (VERSION == "FILE"){
        ifs.open("good_s.in");
        ofs.open("good_s.out");
        is = &ifs;
        os = &ofs;
    }
    return solution(*is,*os);
}
