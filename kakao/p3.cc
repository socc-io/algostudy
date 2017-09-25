#include <string>
#include <iostream>

using namespace std;

string s;
int s_len;

inline bool small(char ch) { return 'a' <= ch && ch <= 'z'; }

int delimiters[1000];
int delimiters_num;

bool used[26];

bool next(int pos, int num, char p1, char p2)
{
	// printf("%d%c ", num, s[pos]);

	if(pos == s_len) {
		return num == 0;
	}

	int npos = pos + 1;
	char ch = s[pos];
	char nch = s[pos + 1];
	if(num == 0) {
		delimiters[delimiters_num++] = pos;
		if(small(ch)) {
			if(!used[ch-'a']) {
				used[ch-'a'] = true;
				if(next(pos, 1, 0, ch)) return true;
				used[ch-'a'] = false;
			}
		} else {
			if(next(pos, 7, 0, 0)) return true;
		}
	} else if(num == 1) {
		if(small(nch)) return false;
		else {
			if(next(npos, 2, 0, p2)) return true;
		}
	} else if(num == 2) {
		if(small(nch)) {
			if(nch == p2) {
				if(next(npos, 6, 0, 0)) return true;
			} else {
				if(!used[nch-'a']) {
					used[nch-'a'] = true;
					if(next(npos, 3, nch, p2)) return true;
					used[nch-'a'] = false;
				}
			}
		} else {
			if(next(npos, 5, 0, p2)) return true;
		}
	} else if(num == 3) {
		if(small(nch)) return false;
		else {
			if(next(npos, 4, p1, p2)) return true;
		}
	} else if(num == 4) {
		if(small(nch)) {
			if(nch == p2) {
				if(next(npos, 6, 0, 0)) return true;
			} else if(nch == p1) {
				if(next(npos, 3, p1, p2)) return true;
			}
		}
	} else if(num == 5) {
		if(small(nch)) {
			if(nch == p2) {
				if(next(npos, 6, 0, 0)) return true;
			}
		} else {
			if(next(npos, 5, 0, p2)) return true;
		}
	} else if(num == 6) {
		if(next(npos, 0, 0, 0)) return true;
	} else if(num == 7) {
		if(small(nch)) {
			if(!used[nch-'a']) {
				used[nch-'a'] = true;
				if(next(npos, 8, nch, 0)) return true;
				used[nch-'a'] = false;
			}
		} else {
			if(next(npos, 10, 0, 0)) return true;
		}
		if(next(npos, 0, 0, 0)) return true;
	} else if(num == 8) {
		if(small(nch)) return false;
		else {
			if(next(npos, 9, p1, 0)) return true;
		}
	} else if(num == 9) {
		if(small(nch)) {
			if(nch == p1) {
				if(next(npos, 8, p1, 0)) return true;
			}
		}
		if(next(npos, 0, 0, 0)) return true;
	} else if(num == 10) {
		if(next(npos, 0, 0, 0)) return true;
		if(!small(nch)) {
			if(next(npos, 10, 0, 0)) return true;
		}
	}

	if(num == 0) delimiters_num--;

	return false;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(string sentence) {
    string answer = "";
    s = sentence;
    s_len = s.length();

    for(int i = 0; i < 26; ++i) {
    	used[i] = false;
    }

    delimiters_num = 0;

    if(next(0, 0, 0, 0)) {
    	int d_idx = 1;
    	for(int i = 0; i < s_len; ++i) {
    		if(i != 0 && delimiters[d_idx] == i && d_idx < delimiters_num) {
    			answer += ' ';
    			d_idx++;
    		}
    		if(!small(s[i])) {
    			answer += s[i];
    		}
    	}
    } else {
    	answer = "invalid";
    }

    return answer;
}

int main(void)
{
	string input;
	cin >> input;

	cout << solution(input) << endl;

	return 0;
}