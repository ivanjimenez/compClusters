#include <stdio.h>
#include <math.h>
#include "mpi.h"
#include <time.h>

/* This example handles a 12 x 12 mesh, on 4 processors only. */
//#define maxn 12

int main( argc, argv )
int argc;
char **argv;
{
    int        rank, value, size, errcnt, toterr, i, j, itcnt;
    int        i_first, i_last;
	clock_t inicio, fin;
	int 	   maxn;
	int		   np;
	double duration;
    MPI_Status status;
    double     diffnorm, gdiffnorm;

    MPI_Init( &argc, &argv );
	
	/* Comprobación número de argumentos correctos. Se pasara maxn */
	if (argc!=3)
	   {
	   printf("Error de Sintaxis. Uso: jacobi_mpi maxn \n");
	   exit(1);
	   }

	/* Lectura de parametros de entrada */
	maxn=atoi(argv[1]);
	np = atoi(argv[2]);
	
    //double     xlocal[(maxn/4)+2][maxn];
    //double     xnew[(maxn/3)+2][maxn];
	double     xlocal[(maxn/np)+2][maxn];
	double     xnew[(maxn/np-1)+2][maxn];

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

   // if (size != 4) MPI_Abort( MPI_COMM_WORLD, 1 );

    /* xlocal[][0] is lower ghostpoints, xlocal[][maxn+2] is upper */

    /* Note that top and bottom processes have one less row of interior points */
    i_first = 1;
    i_last  = maxn/size;
    if (rank == 0)        i_first++;
    if (rank == size - 1) i_last--;

    /* Fill the data as specified */
    for (i=1; i<=maxn/size; i++) 
	for (j=0; j<maxn; j++) 
	    xlocal[i][j] = rank;
    for (j=0; j<maxn; j++) {
	xlocal[i_first-1][j] = -1;
	xlocal[i_last+1][j] = -1;
    }
	
inicio = clock();

    itcnt = 0;
    do {
	/* Send up unless I'm at the top, then receive from below */
	/* Note the use of xlocal[i] for &xlocal[i][0] */
	if (rank < size - 1) 
	    MPI_Send( xlocal[maxn/size], maxn, MPI_DOUBLE, rank + 1, 0, 
		      MPI_COMM_WORLD );
	if (rank > 0)
	    MPI_Recv( xlocal[0], maxn, MPI_DOUBLE, rank - 1, 0, 
		      MPI_COMM_WORLD, &status );
	/* Send down unless I'm at the bottom */
	if (rank > 0) 
	    MPI_Send( xlocal[1], maxn, MPI_DOUBLE, rank - 1, 1, 
		      MPI_COMM_WORLD );
	if (rank < size - 1) 
	    MPI_Recv( xlocal[maxn/size+1], maxn, MPI_DOUBLE, rank + 1, 1, 
		      MPI_COMM_WORLD, &status );
	
	/* Compute new values (but not on boundary) */
	itcnt ++;
	diffnorm = 0.0;
	for (i=i_first; i<=i_last; i++) 
	    for (j=1; j<maxn-1; j++) {
		xnew[i][j] = (xlocal[i][j+1] + xlocal[i][j-1] +
			      xlocal[i+1][j] + xlocal[i-1][j]) / 4.0;
		diffnorm += (xnew[i][j] - xlocal[i][j]) * 
		            (xnew[i][j] - xlocal[i][j]);
	    }
	/* Only transfer the interior points */
	for (i=i_first; i<=i_last; i++) 
	    for (j=1; j<maxn-1; j++) 
		xlocal[i][j] = xnew[i][j];

	MPI_Allreduce( &diffnorm, &gdiffnorm, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD );
	gdiffnorm = sqrt( gdiffnorm );
	if (rank == 0) printf( "At iteration %d, diff is %e\n", itcnt, gdiffnorm );
    } while (gdiffnorm > 1.0e-2 && itcnt < 100);

    MPI_Finalize( );
	fin = clock();
	duration = (double)(fin - inicio) / CLOCKS_PER_SEC;

	printf("Jacobi paralelo mpi: %2.5f segundos\n", duration );
    return 0;
}
