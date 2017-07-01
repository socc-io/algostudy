/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>

using namespace std;

int Answer;
int N;
int costs[200000];
int descending;

int do_task()
{
	cin >> N;
	if(N < 1) return 0;
	for(int i=0; i<N; ++i) {
		cin >> costs[i];
	}

	int down_up = 0;
	int up_down = 0;
	descending = (costs[0] >= costs[1]);

	for(int i=2; i<N; ++i) {
		if(costs[i-1] > costs[i]) { // down
			if(!descending) {
				descending = 1;
				up_down++;
			}
		}
		else if(costs[i-1] < costs[i]) { // up
			if(descending) {
				descending = 0;
				down_up++;
			}
		}
	}

	return 2 * (up_down + (1 - descending));
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