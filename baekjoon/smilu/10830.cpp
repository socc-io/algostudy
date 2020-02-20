#include <cstdio>

#define MOD 1000

typedef unsigned long long llu;

int n;
llu b;

int A[5][5];
int B[5][5];
int R[5][5];

void multiply(int R1[][5], int R2[][5], int to[][5]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      to[i][j] = 0;
      for (int k = 0; k < n; k++) {
        to[i][j] += R1[i][k] * R2[k][j];
      }
      to[i][j] %= MOD;
    }
  }
}

void copy(int from[][5], int to[][5]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      to[i][j] = from[i][j];
    }
  }
}

void print(int mat[][5]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", mat[i][j]);
    }
    puts("");
  }
}

int main(void)
{
  scanf("%d%llu", &n, &b);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &A[i][j]);
    }
  }
  for (int i = 0; i < n; i++) R[i][i] = 1;

  while(b) {
    if (b & 1) {
      multiply(R, A, B);
      copy(B, R);
    }
    multiply(A, A, B);
    copy(B, A);
    b >>= 1;
  }

  print(R);
}