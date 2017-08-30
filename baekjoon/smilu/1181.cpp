#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string words[20000];

bool compare(const string &A, const string &B) {
	unsigned int a_len = A.length();
	unsigned int b_len = B.length();

	if(a_len == b_len) {
		for(int i = 0; i < a_len; ++i) {
			if(A[i] == B[i]) continue;
			return A[i] < B[i];
		}
		return false;
	} else {
		return a_len < b_len;
	}
}

int main(void)
{
	int N;
	scanf("%d", &N);

	for(int i = 0; i < N; ++i) {
		cin >> words[i];
	}

	sort(words, words + N, compare);

	for(int i = 0; i < N; ++i) {
		if(i > 0 && words[i] ==  words[i-1]) continue;
		cout << words[i] << endl;
	}
}