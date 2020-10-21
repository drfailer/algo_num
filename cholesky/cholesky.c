#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <
#define LEN 3
#define EXAMPLE 10

int nbtours;

void make_R(float **matrix, float **r, int n) {
  int i, j, k;   // loop var
  float sum = 0; // Used to calculate the sum of r_ki*r_kj
  float s;
  for (i = 0; i < n; i++) {
    s = matrix[i][i];
    for (j = 0; j < i; j++) {
      s -= r[j][i] * r[j][i];
      nbtours++;
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
          nbtours++;
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
      nbtours++;
    }
  }
}

void solver_cholesky(float **matrix, float *solus_x, float *b, int n) {
  int i, j;
  float tmp;
  float *solus_y = malloc(n * sizeof(float));
  /*Creation of the matrix  R:*/
  float **r = create_mat(n);
  mat_0(r, n);
  make_R(matrix, r, n);
  /*************************************************************************/
  /*Resolution de R^T * y = b*/
  transpose(r, n);
  for (i = 0; i < n; i++) {
    tmp = b[i];
    for (j = 0; j < i; j++) {
      tmp -= solus_y[j] * r[i][j];
      nbtours++;
    }
    solus_y[i] = tmp / r[i][i];
  }
  /*Solving R * x = y*/
  transpose(r, n);
  for (i = (n - 1); i >= 0; i--) {
    for (j = (n - 1); j > i; j--) {
      solus_y[i] -= solus_x[j] * r[i][j];
      nbtours++;
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

void show(float **matrix, int n){
  int i, j;
  for (i = 0; i < n; i++) {
    printf("|");
    for (j = 0; j < n; j++) {
      printf(" %f |", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  nbtours = 0;
  int i;
  float *solus = malloc(LEN * sizeof(float));
  if (solus == NULL)
    exit(EXIT_FAILURE);
  float *b = malloc(LEN * sizeof(float));
  if (b == NULL)
    exit(EXIT_FAILURE);
  for (i = 0; i < LEN; i++) {
    b[i] = 1;
  }
  float **matrix = create_mat(LEN);
  mat(matrix, LEN, EXAMPLE);
  show(matrix, LEN);
  solver_cholesky(matrix, solus, b, LEN);
  // Print solutions
  for (i = 0; i < LEN; i++) {
    printf("%f\n", solus[i]);
  }
  printf("nb itération: %d\n", nbtours);
  /*FREE*/
  free(solus);
  free(b);
  for (i = 0; i < LEN; i++) {
    free(matrix[i]);
  }
  free(matrix);
  return 0;
}
