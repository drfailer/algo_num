#include <stdlib.h>
#include <math.h>

// return nul matrix nxn
void mat_0(float **tab, int n){
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tab[i][j] = 0;
    }
  }
}

void bord(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i == j)
        tab[i - 1][j - 1] = 1;
      else if (i == 1) {
        tab[0][j - 1] = powf(2, 1 - j);
        tab[j - 1][0] = powf(2, 1 - j);
      } else
        tab[i - 1][j - 1] = 0;
    }
  }
}

void ding_dong(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      tab[i - 1][j - 1] = 1.0 / 2 * (n - i - j + 1.5);
    }
  }
}

void franc(float **tab, int n){
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i >= j+2)
	tab[i-1][j-1] = 0;
      else	
	tab[i-1][j-1] = (i < j)? i:j;
    }
  }
}

void hilbert_1(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      tab[i - 1][j - 1] = 1.0 / (i + j - 1);
    }
  }
}

void hilbert_2(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      tab[i - 1][j - 1] = 1.0 / (i + j + 1);
    }
  }
}

void kms(float **tab, int n){
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      tab[i-1][j-1] = powf(0.5, i-j);
    }
  }
}

void lehmer(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i <= j)
        tab[i - 1][j - 1] = (float)i / j;
      else
        tab[i - 1][j - 1] = (float)j / i;
    }
  }
}

void lotkin(float **tab, int n) {
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i == 1)
        tab[i - 1][j - 1] = 1;
      else
        tab[i - 1][j - 1] = 1.0 / (i + j - 1);
    }
  }
}

void moler(float **tab, int n){
  int i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (i == j)
	tab[i-1][j-1] = i;
      else
	tab[i-1][j-1] = (i < j)? (i-2):(j-2);
    }
  }
}

void mat(float **mat, int n, int type_mat) {
  switch (type_mat) {
  case 1:
    bord(mat, n);
    break;
  case 2:
    ding_dong(mat, n);
    break;
  case 3:
    franc(mat, n);
    break;
  case 4:
    hilbert_1(mat, n);
    break;
  case 5:
    hilbert_2(mat, n);
    break;
  case 6:
    kms(mat, n);
    break;
  case 7:
    lehmer(mat, n);
    break;
  case 8:
    lotkin(mat, n);
    break;
  case 9:
    moler(mat, n);
    break;
  default:
    break;
  }
}

float **create_mat(int n){
  int i;
  float ** mat = NULL;
  mat = (float**) malloc(n*sizeof(float*));
  if (mat == NULL)
    exit(EXIT_FAILURE);
  for (i = 0; i < n; i++) {
    mat[i] = (float*) malloc(n*sizeof(float));
    if (mat[i] == NULL)
      exit(EXIT_FAILURE);
  }
  return mat;
}
