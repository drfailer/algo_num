#include "matrix_tp2.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define LEN 4
#define SIGMA 0.0000001
#define MAX 100
#define EXAMPLE 2

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

void gauss_seidel(float **matrix, float *b, float *solus_k, int n) {
  int i, j;
  int compt = 0;
  int bool = 1;
  float *solus_k1 = malloc(n * sizeof(float));
  while (bool &&compt < MAX) {
    for (i = 0; i < n; i++) {
      solus_k1[i] = b[i];
      for (j = 0; j < i; j++) {
        solus_k1[i] -= matrix[i][j] * solus_k1[j];
      }
      for (j = i + 1; j < n; j++) {
        solus_k1[i] -= matrix[i][j] * solus_k[j];
      }
      solus_k1[i] /= matrix[i][i];
    }
    bool = test(solus_k1, solus_k, n);
    for (i = 0; i < n; i++) {
      solus_k[i] = solus_k1[i];
    }
    compt++;
  }
  printf("Nb tours: %d\n", compt);
  // FREE
  free(solus_k1);
}

void show(float **mat, int n){
  int i, j;
  for (i = 0; i < n; i++) {
    printf("|");
    for (j = 0; j < n; j++) {
      printf(" %f |", mat[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int i;
  // init b
  float *b = malloc(LEN * sizeof(float));
  if (b == NULL)
    exit(EXIT_FAILURE);
  // init solus
  float *solus = malloc(LEN * sizeof(float));
  if (solus == NULL)
    exit(EXIT_FAILURE);
  for (i = 0; i < LEN; i++)
    solus[i] = 1;
  // alloc matrix
  float **matrix = create_mat(LEN);
  // Initialise matrix en fonction de l'exemple choisit
  init_mat(matrix, b, LEN, EXAMPLE);
  printf("\n");
  show(matrix, LEN);
  gauss_seidel(matrix, b, solus, LEN);
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