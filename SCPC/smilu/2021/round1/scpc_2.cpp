/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

using namespace std;

int Answer;

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

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		int n, t;
    cin >> n >> t;
    string s; cin >> s;
    for (int i = 0; i < n; i++) s[i] -= '0';

    vector<int> q(n, -1);

    for (int i = 0; i < t && i < n; i++) {
      if (i+t < n) q[i+t] = s[i];
      if (n-1-i-t >= 0) q[n-1-i-t] = s[n-1-i];
    }

    for (int i = 0; i < n; i++) {
      if (s[i] == 0) {
        if (i-t >= 0) q[i-t] = 0;
        if (i+t <  n) q[i+t] = 0;
      }
    }

    for (int i = 0; i < n; i++) {
      if (q[i] == 0) {
        if (i+2*t <  n && s[i+t]) q[i+2*t] = 1;
        if (i-2*t >= 0 && s[i-t]) q[i-2*t] = 1;
      }
    }
    
    for (int i = 0; i < n; i++) {
      if (q[i] != -1) continue;
      int cnt = 0;
      int f = 0;
      while (i + cnt*2*t < n && q[i + cnt*2*t] == -1) {
        q[i + cnt*2*t] = f;
        f = 1-f;
        ++cnt;
      }
    }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		for (int i = 0; i < n; i++) {
      cout << (char) ((q[i] == -1 ? 2 : q[i]) + '0');
    } cout << '\n';
	}

	return 0;//Your program should return 0 on normal termination.
}