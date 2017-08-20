#include <cstdio>

#define S (1.0/6.0)

const double base[7][7] = {
	S, S, S, S, S, S, 1,
	1, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0,
	0, 0, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 0, 0, 1
};

struct matrix {
	double v[7][7];
	void mult(matrix &b) {
		matrix tmp;
		for(int i = 0; i < 7; ++i) for(int j = 0; j < 7; ++j) {
			tmp.v[i][j] = 0;
			for(int k = 0; k < 7; ++k) {
				tmp.v[i][j] += v[i][k] * b.v[k][j];
			}
		}
		for(int i = 0; i < 7; ++i) for(int j = 0; j < 7; ++j) v[i][j] = tmp.v[i][j];
	}
};

int main(void)
{
	int N;
	matrix B, ans;
	scanf("%d", &N);
	for(int i = 0; i < 7; ++i) for(int j = 0; j < 7; ++j) {
		B.v[i][j] = base[i][j];
		ans.v[i][j] = (i == j);
	}
	while(N) {
		if(N & 1) {
			ans.mult(B);
		}
		B.mult(B);
		N >>= 1;
	}
	printf("%.12lf", ans.v[0][6]);
	return 0;
}