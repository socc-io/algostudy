#include <iostream>
#include <string.h>
#include <vector>
#include <list>

using namespace std;

typedef list< pair<int, int> > pair_list;

char S[1000000];
int S_len;
pair_list chunks;

int Answer;

int is_closer(char ch)
{
	if(ch == ')' || ch == ']' || ch == '}') return 1;
	return 0;
}

int is_pair(char a, char b)
{
	if(a == '(' && b == ')') return 1;
	if(a == '[' && b == ']') return 1;
	if(a == '{' && b == '}') return 1;
	return 0;
}

int merge_chunks()
{
	int did_something = 0;
	for(pair_list::iterator it = chunks.begin(); it != chunks.end(); ++it) {
		// .printf("at: %d\n", it->first);
		for(;;) {
			pair_list::iterator next = it;
			++next;

			if(next == chunks.end()) {
				return did_something;
			}

			if(it->first + it->second == next->first) {
				// printf("merge: (%d, %d), (%d, %d)\n", it->first, it->second, next->first, next->second);
				it->second += next->second;
				chunks.erase(next);
				did_something = 1;
			} else {
				break;
			}
		}
	}
	return did_something;
}

int feed_chunks()
{
	int did_something = 0;
	for(pair_list::iterator it = chunks.begin(); it != chunks.end(); ++it) {
		for(;;) {
			if(it->first <= 0) break;
			char left_ch = S[it->first - 1];

			if(it->first + it->second >= S_len) break;
			char right_ch = S[it->first + it->second];

			if(is_pair(left_ch, right_ch)) {
				it->first -= 1;
				it->second += 2;
				did_something = 1;
				// printf("feed: %d, %d => %d, %d\n", it->first+1, it->second-2, it->first, it->second);
			} else {
				break;
			}
		}
	}
	return did_something;
}

int do_task(void)
{
	chunks.clear();
	cin >> S;
	S_len = strlen(S);
	for(int i=1; i<S_len; ++i) {  // find minimum chunks
		if(is_pair(S[i-1], S[i])) {
			chunks.push_back(make_pair(i-1, 2));
			// printf("found: %d, %d\n", i-1, i);
		}
	}

	int merged, feed;
	do {
		merged = merge_chunks(); 
		feed = feed_chunks();
	} while(merged || feed);

	int max_length = 0;
	for(pair_list::iterator it = chunks.begin(); it != chunks.end(); ++it) {
		if(max_length < it->second) {
			max_length = it->second;
		}
	}

	return max_length;
}

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = do_task();
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}