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
	int i,j,k,n;
 
	double *A,*B;  

	clock_t inicio, fin;
	double  duration;
	int iter;
	
	
	/* Comprobación número de argumentos correctos. Se pasaran m n k */
	if (argc!=2)
	   {
	   printf("Error de Sintaxis. Uso: jacobi_seq n \n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	n=atoi(argv[1]);

	/* Dimensionado de las matrices, utilizando funciones propias */
	
	
	A=dmatrix(n,n); //Esta es la matriz en la que resolveremos el sistema
	B=dmatrix(n,n); 
	

	/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matrixA

		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				M(A,i,j,n) = 0.0;
	
	//matrizB

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			M(B,i,j,n) = 0.0;
	

inicio = clock();


for (iter=0; iter<100;iter++){
	
	for (i=1; i<n-1; i++){
		for (j=1; j<n-1; j++){
			M(B,i,j,n) = 0.25 * (M(A,i-1,j,n) + M(A,i+1,j,n) + M(A,i,j+1,n) + M(A,i,j-1,n));
		}
	}
	// Utilizamos otra vez la matriz V como resultado
	for (i=1; i<n-1; i++){
		for (j=1; j<n-1; j++){
			M(A,i,j,n) = M(B,i,j,n);
		}
	}
}
printf("Estoy antes de imprimir\n");
// Imprime resultado
   for (j=0; j<n; j++){
       for (i=0; i<n; i++){
           printf("A[%d,%d]=%d\n", i,j,M(A,i,j,n));
       }
      
   }
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;

printf("A*x=b: %2.5f segundos\n", duration );


}
