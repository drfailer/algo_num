#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LEN 3

void make_R(float **matrix, float **r, int n) {
  int i, j, k;   // loop var
  float sum = 0; // Used to calculate the sum of r_ki*r_kj
  float s;
  for (i = 0; i < n; i++) {
    s = matrix[i][i];
    for (j = 0; j < i; j++) {
      s -= r[j][i] * r[j][i];
    }
    if (s <= 0) {
      printf("La matrice n'est pas définie positive\n");
      exit(EXIT_FAILURE);
    } else {
      r[i][i] = sqrtf(s);
      for (j = (i + 1); j < n; j++) {
        sum = 0;
        for (k = 0; k < i; k++) {
          sum += r[k][i] * r[k][j];
        }
        r[i][j] = (matrix[i][j] - sum) / r[i][i];
      }
    }
  }
}

// transpose matrix
void transpose(float **matrix, int n) {
  int i, j;
  float tmp;
  for (i = 0; i < n; i++) {
    for (j = (i + 1); j < n; j++) {
      tmp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = tmp;
    }
  }
}

void solver_cholesky(float **matrix, float *solus_x, float *b, int n) {
  int i, j;
  float *solus_y = malloc(n * sizeof(float));
  /*Creation of the matrix  R:*/
  float **r = malloc(n * sizeof(float *));
  for (i = 0; i < n; i++) {
    r[i] = malloc(n * sizeof(float));
  }
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      r[i][j] = 0;
    }
  }
  make_R(matrix, r, n);
  /*************************************************************************/
  /*Resolution de R^T * y = b*/
  transpose(r, n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < i; j++) {
      b[i] -= solus_y[j] * r[i][j];
    }
    solus_y[i] = b[i] / r[i][i];
  }
  /*Solving R * x = y*/
  transpose(r, n);
  for (i = (n - 1); i >= 0; i--) {
    for (j = (n - 1); j > i; j--) {
      solus_y[i] -= solus_x[j] * r[i][j];
    }
    solus_x[i] = solus_y[i] / r[i][i];
  }
  /*FREE*/
  free(solus_y);
  for (i = 0; i < n; i++) {
    free(r[i]);
  }
  free(r);
}

int main() {
  int i;
  float *solus = malloc(LEN * sizeof(float));
  float *b = malloc(LEN * sizeof(float));
  // alloc table matrix
  float **matrix = (float **)malloc(LEN * sizeof(float *));
  for (i = 0; i < LEN; i++) {
    matrix[i] = (float *)malloc(LEN * sizeof(float));
  }
  // TODO: Init b properly
  b[0] = 1;
  b[1] = 1;
  b[2] = 1;
  // TODO: Init matrix properly
  matrix[0][0] = 64;
  matrix[0][1] = 40;
  matrix[0][2] = 24;
  matrix[1][0] = 40;
  matrix[1][1] = 29;
  matrix[1][2] = 17;
  matrix[2][0] = 24;
  matrix[2][1] = 17;
  matrix[2][2] = 19;

  solver_cholesky(matrix, solus, b, LEN);
  // Print solutions
  for (i = 0; i < LEN; i++) {
    printf("%f\n", solus[i]);
  }
  /*FREE*/
  free(solus);
  free(b);
  for (i = 0; i < LEN; i++) {
    free(matrix[i]);
  }
  free(matrix);
  return 0;
}
