#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

int iteration; //variables compteur du nombres d'opérations sur la matrice.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void normaLigne        (float ** A, float * B, int n, int q, int j);
void echangeLigne      (float ** A, float * B, int n, int q, int k);
void soustractionLignes(float ** A, float * B, int n, int i, int j, int k);
void gauss			   (float ** A, float * B, int n);
float * resolution	   (float ** A, float * B, int n);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main ()
{
	iteration = 0;
	int i,j,n;

	printf("(GaussPivot)Taille matrices \n");
	scanf("%d",&n);

	float Tdep = clock();
	float *  B = (float * ) malloc(n*sizeof(float  ));

	//Initialisation de la matrice B.
	for (i = 0; i < n; i++)
	{
		B[i] = 1;
	}

	float ** A = create_mat(n);
	mat(A, n, 2);

	//affichage matrice 
	for (i = 0; i<n; i++)
	{
		for(j = 0; j<n;j++)
		{
			printf("%f ,", A[i][j]);
		}
		printf("|   %f", B[i]);
		printf("\n");
	}

	gauss(A,B,n);
	printf("\n");
	
	//Affichage matrice fin gauss
	for (i = 0; i<n; i++)
	{
		for(j = 0; j<n;j++)
		{
			printf("%f ,", A[i][j]);
		}

		printf("|   %f", B[i]);
		printf("\n");
	}

	//affichage du temps d'execution et de la complexité pratique.
	float Tfin = clock();
	printf("\nNombres d'iterations : %d\n", iteration );
	printf("Temps d'éxécution : %f", (Tfin - Tdep)/1000);

    // trouver matrice solution 
	float * solution = (float *) malloc(n*sizeof(float));
	solution = resolution(A,B,n);

	//affichage de la solution
	printf("[ ");
	for(i=0 ;i<n; i++)
	{
		printf("%.1f ,",solution[i]);
	}
	printf("\b]\n");


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	free(B);free(solution);
	for (int i = 0; i < n; i++)
	{
		free(A[i]);
	}
	free(A);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void normaLigne(float ** A, float * B, int n, int q, int j)
{
	int ji;
	float tmp = A[q][j];
	
	// Division de chaque éléments de la ligne q de matrice A & B: "normalisation de la ligne"
	for(ji = q;ji < n;ji++)
	{
		iteration++;
		A[q][ji] = A[q][ji] / tmp;
	}
	B[q] = B[q]/tmp;
}
void echangeLigne(float ** A, float * B, int n, int q, int k)
{
	float tmp;
	int j;
	for (j = 0; j<n ;j++)
	{
		iteration++;
		tmp     = A[k][j];
		A[k][j] = A[q][j];
		A[q][j] = tmp;
	} 

	tmp  = B[k] ;
    B[k] = B[q];
    B[q] = tmp;
}
void soustractionLignes(float ** A, float * B, int n, int i, int j, int k)
{
	int ji;
	float tmp = A[i][j];

	for(ji = 0; ji < n; ji++)
	{
		iteration++;
		A[i][ji] = A[i][ji] - tmp*A[k][ji];
	}
	B[i] -= tmp * B[k];
}

void gauss(float ** A,float * B,int n)
{
	int i, j, k,test, q;
	k = -1;													//indice de ligne du pivot

	for (j = 0; j < n; j++)									//indice de colonne
	{
		test = 0;

		for (i = k+1; i < n; i++) 							//test de l'éxistence du prochain pivot
			{
				if(A[i][j]!=0) {test = 1; break;}
			}
		
		if (test)											//Si teste concluant..
		{
			k++;											//MAJ de l'indice de ligne du pivot
			q = i;											//récupération de la ligne du prochain pivot(trouvé avec le teste)
			normaLigne(A,B,n,q,j);							//normalisation de la ligne
			if (q!=k) echangeLigne(A,B,n,q,k);				//mise du pivot au bon endroit
			
			for (i = k+1; i < n; i++)						//élimination des valeurs sous le pivot
			{
				soustractionLignes(A, B, n, i, j, k);
			}
		}
	}
}

float * resolution(float ** A, float * B, int n)
{
	float * X = (float *)malloc(n*sizeof(float)); 			
	float somme;
	
	for (int i = n-1; i>=0; i--)							//indice de la ligne
	{
		iteration++;
		somme = 0;
		for (int j = n-1; j>i; j--)							//indice de la colonne
		{
			somme += A[i][j]*X[j];
		}
		X[i] = (B[i]-somme);
	}
	return X;
}