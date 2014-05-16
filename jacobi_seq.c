/* Algoritmo de jacobi 
 * @Autor: Iván Jiménez
 *
 * Operación A*x= b
 * Algoritmo secuencial de Jacobi
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memoryfun.h"
#include <math.h>

int main(int argc, char **argv)
{
	
	int result;
	int i,j,l;
	int m,n,k,lda,ldb;
	double *A,*B;

	clock_t inicio, fin;
	double  duration;
	
	/* Comprobación número de argumentos correctos. Se pasaran m n k */
	if (argc!=2)
	   {
	   printf("Error de Sintaxis. Uso: jacobi_seq n \n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	n=atoi(argv[1]);

	/* Dimensionado de las matrices, utilizando funciones propias */
	lda=n; ldb=n; 
	A=dmatrix(n,n); B=dmatrix(n,n); 

	/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matrixA 

		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				M(A,i,j,lda) = 0.0;
	
	//matrizB:: Está será nuestra matriz transpuesta

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			M(B,i,j,ldb) = 0.0;
	
				
	
// Computa la operación: cblas.dot <- X^T*Y

inicio = clock();

printf("No hemos hecho nada\n");
		 
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;
printf("%d %d\n", n, result);
printf("A*x=b: %2.5f segundos\n", duration );


}
