#include <iostream>

using namespace std;

int INFINITE;
int N, N2;
int *mingraph;

int main(int argc, char** argv)
{
	INFINITE = (1 << 30) - 1;
	// cout << "infinite : " << INFINITE << endl;
	cin >> N;
	N2 = N * N;
	mingraph = new int[N2];
	for(int i=0;i<N2;++i) {
		cin >> mingraph[i];
		if(mingraph[i] == 0) mingraph[i] = INFINITE;
	}

	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			for(int k=0;k<N;++k) {
				int a = j*N+k;
				int b = j*N+i;
				int c = i*N+k;
				int newval = mingraph[b] + mingraph[c];
				if(mingraph[a] > newval) {
					mingraph[a] = newval;
					// cout << "updated : " << newval << endl;
				}
			}
		}
	}

	for(int i=0;i<N;++i){
		int iN = i*N;
		for(int j=0;j<N;++j) {
			// cout << mingraph[iN+j] << endl;
			cout << (mingraph[iN+j] == INFINITE ? 0 : 1) << " ";
		}
		cout << endl;
	}

	return 0;
}