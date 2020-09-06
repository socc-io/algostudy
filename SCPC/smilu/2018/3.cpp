#include <iostream>

using namespace std; 

int N, M;
char tile[100][100];

char from_R[100][100];
char from_C[100][100];

char R[100][100];
char C[100][100];

int try_R(int x, int idx, int v);
int try_C(int y, int idx, int v); 

void print_2(int a)
{
	if(a < 10) {
		cout << "0" << a;
	} else {
		cout << a;
	}
}

int try_R(int x, int idx, int v)
{
	if(R[x][idx] != -1) {
		if(R[x][idx] == v) return 1;
		else return 0;
	}

	R[x][idx] = v;
	int succ = 1;
	for(int y=0; y<M; ++y) {
		if(from_R[x][y] == idx) {
			if(!try_C(y, from_C[x][y], (int)(v == tile[x][y]))) {
				succ = 0;
				break;
			}
		}
	}
	if(!succ) {
		R[x][idx] = -1;
		return 0;
	}
	return 1;
}

int try_C(int y, int idx, int v)
{
	if(C[y][idx] != -1) {
		if(C[y][idx] == v) return 1;
		else return 0;
	}

	C[y][idx] = v;
	int succ = 1;
	for(int x=0; x<N; ++x) {
		if(from_C[x][y] == idx) {
			if(!try_R(x, from_R[x][y], (int)(v == tile[x][y]))) {
				succ = 0;
				break;
			}
		}
	}
	if(!succ) {
		C[y][idx] = -1;
		return 0;
	}
	return 1;
}

int search()
{
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			if(R[i][j] == -1) {
				if((!try_R(i, j, 0)) && (!try_R(i, j, 1))) {
					return 0;
				}
			}
		}
	}
	for(int i=0; i<M; ++i) {
		for(int j=0; j<N; ++j) {
			if(C[i][j] == -1) {
				if((!try_C(i, j, 0)) && !(try_C(i, j, 1))) {
					return 0;
				}
			}
		}
	}
	return 1;
}

void do_task()
{
	cin >> N >> M;
	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			R[i][j] = 0;
			C[i][j] = 0;
		}
	}

	for(int i=0; i<N; ++i) {
		for(int j=0; j<M; ++j) {
			int a, b, c;
			cin >> a >> b >> c;
			tile[i][j] = a;
			from_R[i][j] = b;
			from_C[i][j] = c;
			R[i][from_R[i][j]] = -1;
			C[j][from_C[i][j]] = -1;
		}
	}

	int succ = search();

	if(succ) {
		for(int i=0; i<M; ++i) {
			for(int j=0; j<N; ++j) {
				if(C[i][j]) {
					cout << "C";
					print_2(i);
					print_2(j);
					cout << " ";
				}
			}
		}
		for(int i=0; i<N; ++i) {
			for(int j=0; j<M; ++j) {
				if(R[i][j]) {
					cout << "R";
					print_2(i);
					print_2(j);
					cout << " ";
				}
			}
		}
	} else {
		cout << "Impossible";
	}
	
	
	cout << endl;
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

	// freopen("3_input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		do_task();
	}

	return 0;//Your program should return 0 on normal termination.
}