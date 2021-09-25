/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int Answer;

int root(vector<int> & par, int a) {
    if (par[a] == a) return a;
    par[a] = root(par, par[a]);
    return par[a];
}

void merge(vector<int> & par, int a, int b) {
    a = root(par, a);
    b = root(par, b);
    par[a] = b;
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

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		int n;
	    cin >> n;
	    vector<int> par(n);
	    for (int i = 0; i < n; i++) par[i] = i;
	    for (int i = 0; i < n; i++) {
	        int v; cin >> v;
	        v += i;
	        if (v >= n) continue;
	        merge(par, i, v);
	    }
	    
	    set<int> s;
	    for (int i = 0; i < n; i++) {
	        s.insert(root(par, i));
	    }
	    
	    Answer = s.size();
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}