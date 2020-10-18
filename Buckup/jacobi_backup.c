#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define LEN 4
#define SIGMA 0.0000001
#define MAX 100

void jacobi(float **matrix, float *b, float *solus_k, int n);
// FIXME:
int test(float *solus_k, float *solus_k1, int n) {
  int i;
  float *tmp = malloc(n * sizeof(float));
  float s_quadra = 0;
  for (i = 0; i < n; i++) {
    tmp[i] = solus_k1[i] - solus_k[i];
    s_quadra += tmp[i] * tmp[i];
  }
  // FREE
  free(tmp);
  return (sqrtf(s_quadra) > SIGMA);
}

int main() {
  int i;
  float *b = malloc(LEN * sizeof(float));
  b[0] = 15;
  b[1] = 15;
  b[2] = 19;
  b[3] = 11;

  float *solus = malloc(LEN * sizeof(float));
  // Init solus
  solus[0] = 1;
  solus[1] = 1;
  solus[2] = 1;
  solus[3] = 1;

  float **matrix = (float **)malloc(LEN * sizeof(float *));
  for (i = 0; i < LEN; i++) {
    matrix[i] = (float *)malloc(LEN * sizeof(float));
  }
  // Init matrix
  matrix[0][0] = 4;
  matrix[0][1] = 1;
  matrix[0][2] = 1;
  matrix[0][3] = 0;
  matrix[1][0] = 1;
  matrix[1][1] = 4;
  matrix[1][2] = 0;
  matrix[1][3] = 1;
  matrix[2][0] = 1;
  matrix[2][1] = 0;
  matrix[2][2] = 4;
  matrix[2][3] = 1;
  matrix[3][0] = 0;
  matrix[3][1] = 1;
  matrix[3][2] = 1;
  matrix[3][3] = 4;

  jacobi(matrix, b, solus, LEN);
  for (i = 0; i < LEN; i++) {
    printf("%f\n", solus[i]);
  }
  // FREE
  free(solus);
  free(b);
  for (i = 0; i < LEN; i++) {
    free(matrix[i]);
  }
  free(matrix);
  return 0;
}

void jacobi(float **matrix, float *b, float *solus_k, int n) {
  int i, j;
  int compt = 0;
  int bool = 1;
  float *solus_k1 = malloc(n * sizeof(float));
  while (bool &&compt < MAX) {
    for (i = 0; i < n; i++) {
      solus_k1[i] = b[i];
      for (j = 0; j < n; j++) {
        if (j != i)
          solus_k1[i] -= matrix[i][j] * solus_k[j];
      }
      solus_k1[i] /= matrix[i][i];
    }
    bool = test(solus_k1, solus_k, n);
    for (i = 0; i < n; i++) {
      solus_k[i] = solus_k1[i]; // At the end of the execution, solus_k contain
                                // the solutions
    }
    compt++;
  }
  // FREE
  free(solus_k1);
}
