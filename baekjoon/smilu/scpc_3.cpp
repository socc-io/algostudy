/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, k;
vector< vector<int> > adj;
int pv;

bool find_route(int src, int dst) {
  vector<int> visit(n+1);
  queue<int> q;
  q.push(src);
  visit[src] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == dst) return true;
    for (int v: adj[u]) {
      if (!visit[v]) {
        q.push(v);
        visit[v] = true;
      }
    }
  }
  return false;
}

int main(int argc, char** argv)
{
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
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////

    cin >> n >> m >> k;
    adj = vector< vector<int> >(n+1);
    pv = 0;

    for (int i = 0; i < m; i++) {
      int a, b; cin >> a >> b;
      adj[a].push_back(b);
    }
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		for (int i = 0; i < k; i++) {
      int a, b; cin >> a >> b;
      if (find_route(b, a)) {
        cout << '1';
        adj[b].push_back(a);
      }
      else {
        cout << '0';
        adj[a].push_back(b);
      }
    } cout << '\n';
	}

	return 0;//Your program should return 0 on normal termination.
}