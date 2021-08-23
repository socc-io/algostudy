/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

ll Answer;

int n, m;
vector< vector<ll> > wei;

int main(int argc, char** argv)
{
	setbuf(stdout, NULL);
	ios::sync_with_stdio(0); cin.tie(0);

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

    cin >> n >> m;
    wei = vector< vector<ll> >(n);
    for (int i = 0; i < n; i++) {
      int l; cin >> l;
      wei[i] = vector<ll>(l);
      for (int j = 0; j < l; j++) {
        cin >> wei[i][j];
      }
			sort(wei[i].begin(), wei[i].end());
    }

		vector< pair<ll, bool> > fs;
		int oc = 0;
		for (int i = 0; i < n; i++) {
			Answer += wei[i][0] + wei[i][1] + wei[i][2] + wei[i][3];
			bool odd = wei[i].size() & 1;
			if (odd) {
				oc++;
				Answer += wei[i][0];
			}
			fs.push_back(make_pair(wei[i][2] + wei[i][3], odd));
		}
		sort(fs.begin(), fs.end());

		ll border = fs[fs.size() - 1].first + fs[fs.size() - 2].first;
		if (fs[fs.size()-1].second && fs[fs.size()-2].second && oc == 2) {
			ll penalty = 0;
			for (int i = 0; i < n; i++) {
				if ((wei[i].size() & 1) == 1) continue;
				penalty += wei[i][0] + wei[i][1];
			}

			if (n == 2) {
				Answer -= border;
			} else {
				ll yield = fs[fs.size()-1].first + fs[fs.size()-3].first;
				ll n_yield = border - penalty;
				Answer -= max(yield, n_yield);
			}
		} else {
			Answer -= border;
		}
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}