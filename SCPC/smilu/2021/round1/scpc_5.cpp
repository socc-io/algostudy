/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;

#define X first
#define Y second

int Answer;

int n;
int nor[100100];
int par[100100];
int sup[100100];

pi root(int x) {
  if (par[x] == x) return {x, 0};
  pi p_res = root(par[x]);
  par[x] = p_res.first;
  sup[x] += p_res.second;
  return {par[x], sup[x]};
}

void query(int a, int b) {
  pi a_res = root(a);
  pi b_res = root(b);

  if (a_res.first != b_res.first) {
    cout << "NC\n";
  } else if (nor[a_res.first]) cout << "CF\n";
  else {
    cout << b_res.second - a_res.second << '\n';
  }
}

void merge(int a, int b, int d) {
  pi a_res = root(a);
  pi b_res = root(b);

  if (a_res.first == b_res.first) {
    int rd = b_res.second - a_res.second;
    if (rd != d) nor[a_res.first] = 1;
  } else {
    int ad = a_res.second, bd = b_res.second;
    a = a_res.first, b = b_res.first;
    par[b] = a;
    sup[b] = d + ad - bd;
    nor[a] |= nor[b];
  }
}

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

    cout << "Case #" << test_case+1 << endl;

    int q;
    cin >> n >> q;
    for (int i = 0; i <= n; i++) par[i] = i;
    for (int i = 0; i <= n; i++) sup[i] = 0;
    for (int i = 0; i <= n; i++) nor[i] = 0;
    while (q--) {
      int cmd, f, t;
      cin >> cmd >> f >> t;
      if (cmd == 1) {
        ll d; cin >> d;
        merge(f, t, d);
      } else {
        query(f, t);
      }
    }
	}

	return 0;//Your program should return 0 on normal termination.
}