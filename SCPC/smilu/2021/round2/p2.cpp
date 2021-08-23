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

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y): x(x), y(y) {}
};

ll ds[8][2] = {
    {0, 0},
    {0, -1},
    {-1, -2},
    {-2, -2},
    {-3, -1},
    {-3, 0},
    {-2, 1},
    {-1, 1},
};

void apply_offset(Point * ps, vector<ll> & indices, int mult) {
    for (int i = 0; i < 8; i++) {
        ps[indices[i]].x += ds[i][0] * mult;
        ps[indices[i]].y += ds[i][1] * mult;
    }
}

ll my_abs(ll x) {
    return x < 0 ? -x : x;
}

ll fn1(vector<ll> arr) {
    sort(arr.begin(), arr.end());
    ll res = 0;
    for (int i = 0; i < 8; i++) {
        res += my_abs(arr[3] - arr[i]);
    }
    return res;
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

        ll k; cin >> k;
        Point ps[8];
        for (int i = 0; i < 8; i++) {
            cin >> ps[i].x >> ps[i].y;
        }
        
        vector<ll> indices(8);
        for (int i = 0; i < 8; i++) indices[i] = i;

        ll min_cost = -1;

        do {
            ll cost = 0;
            apply_offset(ps, indices, k);
            vector<ll> buf(8);
            for (int i = 0; i < 8; i++) buf[i] = ps[i].x;
            cost += fn1(buf);
            for (int i = 0; i < 8; i++) buf[i] = ps[i].y;
            cost += fn1(buf);
            apply_offset(ps, indices, -k);
            if (min_cost == -1 || min_cost > cost) {
                min_cost = cost;
            }
        } while (next_permutation(indices.begin(), indices.end()));

		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << min_cost << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}