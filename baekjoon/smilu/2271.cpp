#include <cstdio>

int T, N;
int A[5000];
int m[5000];
int M[5000];

bool check()
{
    for(int i = 0; i < N; ++i) {
        m[i] = 0;
        M[i] = 0;
    }
    for(int p = 0; p < N-3; ++p) {
        m[p+1] = p+1;
        M[p+1] = p+1;
        for(int i = p+2; i < N && m[i] <= p; ++i) {
            m[i] = A[m[i-1]] > A[i] ? i : m[i-1];
        }
        for(int i = p+2; i < N && M[i] <= p; ++i) {
            M[i] = A[M[i-1]] < A[i] ? i : M[i-1];
        }
        for(int s = p+3; s < N; ++s) {
            if((A[p] - A[s])*(M[s-1] - m[s-1]) > 0)
                if(A[M[s-1]] > A[p] && A[M[s-1]] > A[s])
                    if(A[m[s-1]] < A[p] && A[m[s-1]] < A[s])
                        return true;
        }
    }
    return false; 
}

int main(void)
{
	scanf("%d", &T);
	for(int t = 0; t < T; ++t) {
		scanf("%d", &N);
		for(int i = 0; i < N; ++i) {
			scanf("%d", A + i);
		}
		puts(check() ? "Yes" : "No");
	}
}
