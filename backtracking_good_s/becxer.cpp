#include <iostream>
#include <fstream>
#define VERSION "STDIN"
using namespace std;

//스트링비교 구현
bool ustrcmp(char* src, char* dst){
	while (*src != NULL && *dst != NULL){
		if (*src++ != *dst++) return false;
	}
	return true;
}

//가장 뒷부분에서 (1~n) 길이별 패턴이 존재하는지 확인한다
bool checkPattern(char arr[100], int count){
	bool isPatternExist = false;
	for (int i = 1; i * 2 <= count; i++){
		if (ustrcmp(&arr[count - i * 2], &arr[count - i])){
			isPatternExist = true;
		}
	}
	return isPatternExist;
}

//순열 길이
int len = 0;

//순열 seq 클래스
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


//스택 구현
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


//수열 seq 를 각 순서마다 1,2,3 을 채워가면서 패턴이 존재하는 검사한다
//푼 방법 : 백트래킹
int solution(istream& in, ostream& out){
	in >> len;
	
	//자료구조 선언 (스택으로 선언함)
	stack<seq*> st = stack<seq*>( );

	//초기값 자료구조에 넣어주기
	for (int i = 2; i >= 0; i--){
		seq* first = new seq((char)('1' + i));
		if (first != NULL) st.push(first);
	}

 	while (true){
		if (st.isEmpty( )) break;
		seq* now = st.pop( );
		//현재 시퀀스가 결과에 적합한지 확인
		if (now->isGoal( )){
			out << now->arr << endl;
			break;
		}else{
			//후보군을 생성한후, 자료구조에 넣음
			//가장 최소값을 구해야 하므로, 321 순서로 추가시퀀스를 생성하여 넣는다.
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

//VERSION 을 FILE 로 고치면, 파일에서 읽고 쓰기
//solution 을 호출해서 문제를 푼다
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
