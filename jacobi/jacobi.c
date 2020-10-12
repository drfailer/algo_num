#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LEN 3
#define SIGMA 0.0000001

void jacobi(float ** matrix, float * b, float * start_point, int n);


/* float calc_error(float ** mat, float * x, float * b, int n){ */
/*   int i, j, k; */
/*   int *tmp = malloc(n*sizeof(float*)); */
/*   float output = 0; */
/*   for(i = 0; i < n; i++){ */
/*     tmp[i] = 0; */
/*     for(j = 0; j < n; j++){ */
/*       tmp[i] += mat[i][j] * x[j]; */
/*     } */
/*   } */
/*   for(i = 0; i < n; i++){ */
/*     tmp[i] -= b[i]; */
/*     output += tmp[i] * tmp[i]; */
/*   } */
/*   printf("%.3f sigma\n",sqrtf(output)); */
/*   free(tmp); */
/*   return sqrtf(output); */
/* } */

int test(float * solus,float * lautre, int n){
  int i;
  float * tmp = malloc(n*sizeof(float));
  float s_quadra;
  for(i = 0; i < n; i++){
	tmp[i]  = solus[i] - lautre[i];
	s_quadra += tmp[i] * tmp[i];
  }
  return sqrtf(s_quadra) > SIGMA;
}

int main(){
  int i;
  float *b = malloc(LEN*sizeof(float));
  b[0] = 8;  b[1] = 3;  b[2] = 8;
  
  float *solus = malloc(LEN*sizeof(float));
  solus[0] = 0;  solus[1] = 0;  solus[2] = 1;
  
  float **matrix = (float**) malloc(LEN*sizeof(float*));
  for (i = 0; i < LEN; i++){
    matrix[i] = (float*) malloc(LEN*sizeof(float));
  }
  matrix[0][0] = 4;   matrix[0][0] = 1;   matrix[0][0] = 0;
  matrix[0][0] = -1;   matrix[0][0] = 3;   matrix[0][0] = 6;
  matrix[0][0] = -2;   matrix[0][0] = -5;   matrix[0][0] = -2;

  jacobi(matrix, b, solus,3);
  free(solus);
  free(b);
  for(i = 0; i<LEN; i++)
    {
      free(matrix[i]); 
    }
  free(matrix);
  return 0;
}

void jacobi(float ** matrix, float * b, float * start_point, int n){
  int i, j;
  float * solus = malloc(n*sizeof(float*));
  
  while (!test(solus, start_point, n)){

    for(i = 0; i < n; i++){
      printf("%.1f, ",start_point[i]);
      solus[i] = b[i];
      for(j = 0; j < n; j++){
	if (j != i)
	  solus[i] -= matrix[i][j] * start_point[j];
      }
      solus[i] /= matrix[i][i];
    }
    for(i = 0; i < n; i++){     
      start_point[i] = solus[i];
      

    }
    printf("\n");
  }
  free(solus);
}
