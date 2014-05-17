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
 
	double *V,*b,*temp;  

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
	
	
	V=dmatrix(n,n); //Esta es la matriz en la que resolveremos el sistem
	b=dmatrix(n,n); 
	temp=dmatrix(n,n);

	/* Relleno de las matrices con valores aleatorios. Uso de macro propia */

	//matrixV

		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				M(V,i,j,n) = 0.0;
	
	//matrizb

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			M(b,i,j,n) = 0.0;
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			M(temp,i,j,n) = 0.0;
	
	
	
	M(b,n/2, n/2,n) = -1.0;
	
	
// Computa la operación: cblas.dot <- X^T*Y

inicio = clock();

printf("Estoy antes\n");
for (iter=0; iter<100;iter++){
	
	for (i=1; i<n-1; i++){
		for (j=1; j<n-1; j++){
			M(temp,i,j,n) = 0.25 * (M(V,i+1,j,n) + M(V,i-1,j,n) + M(V,i,j+1,n) + M(V,i,j-1,n) - M(b,i,j,n));
		}
	}
	
	for (i=1; i<n-1; i++){
		for (j=1; j<n-1; j++){
			M(V,i,j,n) = M(temp,i,j,n);
		}
	}
}
printf("Estoy antes de imprimir\n");
// Imprime resultado
   for (j=0; j<n; j++){
       for (i=0; i<n; i++){
           printf("V[%d,%d]=%d\n", i,j,M(V,i,j,n));
       }
      
   }
                  
fin = clock();
duration = (double)(fin - inicio) / CLOCKS_PER_SEC;

printf("A*x=b: %2.5f segundos\n", duration );


}
