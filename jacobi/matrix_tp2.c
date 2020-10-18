#include <stdlib.h>

float **create_mat(int n){
  int i;
  float **mat = NULL;
  mat = (float **) malloc(n*sizeof(float*));
  if (mat == NULL)
    exit(EXIT_FAILURE);
  for (i = 0; i < n; i++) {
    mat[i] = (float *) malloc(n*sizeof(float));
    if (mat[i] == NULL)
      exit(EXIT_FAILURE);
  }
  return mat;
}

void ex_0(float **mat, float *b, int n){
  if (n < 4)
    exit(EXIT_FAILURE);
  else {
    b[0] = 15;
    b[1] = 15;
    b[2] = 19;
    b[3] = 11;
    mat[0][0] = 4;
    mat[0][1] = 1;
    mat[0][2] = 1;
    mat[0][3] = 0;
    mat[1][0] = 1;
    mat[1][1] = 4;
    mat[1][2] = 0;
    mat[1][3] = 1;
    mat[2][0] = 1;
    mat[2][1] = 0;
    mat[2][2] = 4;
    mat[2][3] = 1;
    mat[3][0] = 0;
    mat[3][1] = 1;
    mat[3][2] = 1;
    mat[3][3] = 4;
  }
}

void init_mat(float **mat, float *b, int n, int example){
  switch (example){
  case 0: ex_0(mat, b, n); break;
  default: break;
  }
}
