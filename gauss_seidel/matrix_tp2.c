#include <stdio.h>
#include <stdlib.h>

float **create_mat(int n) {
  int i;
  float **mat = NULL;
  mat = (float **)malloc(n * sizeof(float *));
  if (mat == NULL)
    exit(EXIT_FAILURE);
  for (i = 0; i < n; i++) {
    mat[i] = (float *)malloc(n * sizeof(float));
    if (mat[i] == NULL)
      exit(EXIT_FAILURE);
  }
  return mat;
}

void ex_1(float **mat, float *b, int n) {
  if (n < 4)
    exit(EXIT_FAILURE);
  else {
    b[0] = 15.005;
    b[1] = 15.005;
    b[2] = 19.005;
    b[3] = 11.005;
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

void ex_2(float **mat, float *b, int n) {
  if (n != 4) {
    printf("error: segmentation fault");
    exit(EXIT_FAILURE);
  } else {
    b[0] = 1.005;
    b[1] = 1.005;
    b[2] = 1.005;
    b[3] = 1.005;
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

void ex_3(float **mat, float *b, int n) {
  if (n != 3) {
    printf("error: segmentation fault");
    exit(EXIT_FAILURE);
  } else {
    b[0] = 2;
    b[0] = -1;
    b[0] = 3;
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 1;
    mat[1][0] = 2;
    mat[1][1] = 2;
    mat[1][2] = 3;
    mat[2][0] = 5;
    mat[2][1] = 1;
    mat[2][2] = 8;
  }
}

void init_mat(float **mat, float *b, int n, int example) {
  switch (example) {
  case 1:
    ex_1(mat, b, n);
    break;
  case 2:
    ex_2(mat, b, n);
    break;
  case 3:
    ex_3(mat, b, n);
  default:
    break;
  }
}
